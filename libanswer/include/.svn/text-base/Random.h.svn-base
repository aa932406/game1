#pragma once

namespace Answer
{
	class ANSWER_EXPORT_SYMBOL Random
	{
	public:
		Random();
		~Random();

	private:
		DISALLOW_COPY_AND_ASSIGN(Random);

	public:
		void init(bool useDevice);
		int generate(int min, int max);		// 两边都能取到

	private:
		int randomInt();

	private:
#ifdef LIBANSWER_WINDOWS
		HCRYPTPROV m_cryptProv;
#endif
#ifdef LIBANSWER_LINUX
		int m_fd;
#endif
	};
}


