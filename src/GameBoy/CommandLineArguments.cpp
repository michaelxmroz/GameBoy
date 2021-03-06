#include "CommandLineArguments.h"

CommandLineParser::CommandLineParser(int argc, char** argv)
{
	Parse(argc, argv);
}

std::string CommandLineParser::GetArgument(const std::string& arg)
{
	if (m_argumentDb.count(arg))
	{
		return m_argumentDb[arg];
	}
	return "";
}

void CommandLineParser::Parse(int argc, char** argv)
{
	int argCount = argc - 1;

	assert(argCount % 2 == 0);

	int iterationCount = argCount / 2;
	for (size_t i = 0; i < iterationCount; i++)
	{
		size_t index = i * 2 + 1;
		std::string key(argv[index]);
		std::string value(argv[index + 1]);
		m_argumentDb.emplace(key, value);
	}
}
