#!/bin/bash
# Cross-compilation build script for gameserver, gateserver, globalserver, dbserver
# Supports: arm64 (native), amd64 (cross-compile)
# Usage: ./cross_build.sh [arm64|amd64] [clean]

set -e

ARCH=${1:-arm64}
ACTION=${2:-build}
PROJECT_DIR=$(cd "$(dirname "$0")/.." && pwd)
BUILD_DIR="$PROJECT_DIR/build-$ARCH"

# Architecture-specific settings
if [ "$ARCH" = "amd64" ]; then
    echo "=== Configuring for x86_64 (amd64) cross-compilation ==="
    CROSS_PREFIX="x86_64-linux-gnu-"
    CXX="${CROSS_PREFIX}g++"
    CC="${CROSS_PREFIX}gcc"
    AR="${CROSS_PREFIX}ar"
    SYSROOT="/tmp/x86_64-sysroot"
    LIBMYSQL_DIR="$SYSROOT/usr/lib/x86_64-linux-gnu"
    MYSQL_INCLUDE="$SYSROOT/usr/include"
    ZLIB_DIR="$SYSROOT/usr/lib/x86_64-linux-gnu"
    BIN_SUFFIX=""
elif [ "$ARCH" = "arm64" ]; then
    echo "=== Configuring for aarch64 (arm64) native build ==="
    CXX="g++"
    CC="gcc"
    AR="ar"
    LIBMYSQL_DIR="/usr/lib/aarch64-linux-gnu"
    MYSQL_INCLUDE="/usr/include"
    ZLIB_DIR="/usr/lib/aarch64-linux-gnu"
    BIN_SUFFIX=""
else
    echo "Usage: $0 [arm64|amd64] [clean]"
    exit 1
fi

echo "CXX=$CXX"
echo "Output dir: $BUILD_DIR"

clean_all() {
    echo "=== Cleaning $ARCH build ==="
    rm -rf "$BUILD_DIR"
}

# Common compiler flags
CFLAGS="-g -O2 -Wall -DLIBANSWER_LINUX -I$PROJECT_DIR/share -I$PROJECT_DIR/libanswer/include -I$MYSQL_INCLUDE/mysql"
LFLAGS="-L$LIBMYSQL_DIR -lmysqlclient -lpthread -lz"

build_libanswer() {
    echo "=== Building libanswer ($ARCH) ==="
    local LIB_DIR="$BUILD_DIR/libanswer"
    mkdir -p "$LIB_DIR"
    
    cd "$PROJECT_DIR/libanswer/src"
    local SRCS=(*.cpp)
    local OBJS=()
    for src in "${SRCS[@]}"; do
        obj="$LIB_DIR/${src%.cpp}.o"
        OBJS+=("$obj")
        if [ "$ACTION" = "clean" ]; then
            rm -f "$obj"
        else
            echo "  Compiling: $src"
            $CXX $CFLAGS -c "$src" -o "$obj"
        fi
    done
    
    if [ "$ACTION" != "clean" ]; then
        echo "  Archiving: libanswer.a"
        $AR rcs "$LIB_DIR/libanswer.a" "${OBJS[@]}"
        echo "  libanswer.a created"
    fi
}

build_subproject() {
    local name="$1"
    echo "=== Building $name ($ARCH) ==="
    local TARGET_DIR="$BUILD_DIR/$name"
    mkdir -p "$TARGET_DIR"
    
    cd "$PROJECT_DIR/$name"
    local SRCS=(*.cpp)
    local OBJS=()
    
    for src in "${SRCS[@]}"; do
        obj="$TARGET_DIR/${src%.cpp}.o"
        OBJS+=("$obj")
        if [ "$ACTION" = "clean" ]; then
            rm -f "$obj"
        else
            echo "  Compiling: $src"
            $CXX $CFLAGS -I"$MYSQL_INCLUDE" -c "$src" -o "$obj"
        fi
    done
    
    if [ "$ACTION" != "clean" ]; then
        local LLIB="-L$BUILD_DIR/libanswer -lanswer"
        echo "  Linking: $name -> $PROJECT_DIR/bin/$ARCH/$name$BIN_SUFFIX"
        mkdir -p "$PROJECT_DIR/bin/$ARCH"
        $CXX -o "$PROJECT_DIR/bin/$ARCH/$name$BIN_SUFFIX" "${OBJS[@]}" $LLIB $LFLAGS
        echo "  Binary created: $PROJECT_DIR/bin/$ARCH/$name$BIN_SUFFIX"
        ls -lh "$PROJECT_DIR/bin/$ARCH/$name$BIN_SUFFIX"
    fi
}

# Execute
if [ "$ACTION" = "clean" ]; then
    clean_all
else
    build_libanswer
    build_subproject "gameserver"
    build_subproject "gateserver"
    build_subproject "globalserver"
    build_subproject "dbserver"
    echo ""
    echo "=== Build complete ($ARCH) ==="
    echo "Binaries in: $PROJECT_DIR/bin/$ARCH/"
    ls -lh "$PROJECT_DIR/bin/$ARCH/"
fi
