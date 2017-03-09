#pragma once
#include "sox.h"
#include <string>

namespace msu
{
	class SoxWrapper
	{
	public:
		SoxWrapper();
		~SoxWrapper();

		bool init(std::string in, std::string out);
		bool trim(unsigned start, unsigned end = 0);
		bool fade(unsigned in, unsigned out = 0, char type = 't');
		bool pad(unsigned start, unsigned end = 0);
		bool tempo(double tempo);
		bool finalize();
		bool clear();
		bool deleteInput(bool in = true);

	private:
		bool addEffect(std::string name, int argc, char** argv, int in_id = 0);
		std::string getTempFile(std::string ext);

		bool m_initialized;
		bool m_finalized;
		int m_temp_counter;
		bool m_delete_input;

		sox_format_t** m_in;
		std::string m_in_name;
		int m_num_in;
		sox_format_t* m_out;
		std::string m_out_name;
		sox_effects_chain_t* m_chain;
		sox_signalinfo_t m_in_signal;
		sox_signalinfo_t m_out_signal;
		sox_encodinginfo_t m_out_encoding;
	};

	class SoxWrapperFactory
	{
	public:
		~SoxWrapperFactory() { delete(m_instance); }
		static SoxWrapper* getInstance()
		{
			if (!m_instance)
				m_instance = new SoxWrapper();

			return m_instance;
		}

	private:
		SoxWrapperFactory();
		static SoxWrapper *m_instance;
	};
}