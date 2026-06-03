#include "stdafx.h"

#include "Random.h"

#include <time.h>

using namespace Answer;

Random::Random()
{
#ifdef LIBANSWER_WINDOWS
	m_cryptProv = NULL;
#endif
#ifdef LIBANSWER_LINUX
	m_fd = -1;
#endif
}

Random::~Random()
{
#ifdef LIBANSWER_WINDOWS
	if (m_cryptProv != NULL)
	{
		CryptReleaseContext(m_cryptProv, 0);
		m_cryptProv = NULL;
	}
#endif
#ifdef LIBANSWER_LINUX
	if (m_fd == -1)
	{
		close(m_fd);
		m_fd = -1;
	}
#endif
}

void Random::init(bool useDevice)
{
	if (useDevice)
	{
#ifdef LIBANSWER_WINDOWS
		if (!CryptAcquireContext(&m_cryptProv, NULL, NULL, PROV_RSA_FULL, 0))
		{
			CryptAcquireContext(&m_cryptProv, NULL, NULL, PROV_RSA_FULL, CRYPT_NEWKEYSET);
		}
#endif
#ifdef LIBANSWER_LINUX
		m_fd = open("/dev/urandom", O_RDONLY);
#endif
	}

	srand(static_cast<unsigned int>(time(NULL)));
}

int Random::generate(int min, int max)
{
	bool bfu=false;
	int32_t nTemp=(max+1-min);
	if(nTemp ==0) return 0;
	if(nTemp<0) 
	{
		nTemp =(-1) * nTemp;
		bfu =true;
	}
	int addon = abs(randomInt())%nTemp;
	if(bfu) addon=addon*(-1);
	return min + addon;
}

int Random::randomInt()
{
	int random = 0;

#ifdef LIBANSWER_WINDOWS
	BYTE *pbBuffer = (BYTE*)(&random);
	if (m_cryptProv != NULL && CryptGenRandom(m_cryptProv, sizeof(int), pbBuffer))
	{
		return random;
	}
#endif
#ifdef LIBANSWER_LINUX
	if (m_fd != -1 && read(m_fd, &random, sizeof(random))!= -1)
	{
		return random;
	}
#endif

	return rand();
}

