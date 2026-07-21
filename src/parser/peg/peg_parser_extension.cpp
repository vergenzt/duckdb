#include "duckdb/parser/peg/peg_parser_extension.hpp"

namespace duckdb {

PEGParserExtensionRegistry &PEGParserExtensionRegistry::Get() {
	static PEGParserExtensionRegistry instance;
	return instance;
}

void PEGParserExtensionRegistry::Register(PEGParserExtension extension) {
	extensions.push_back(std::move(extension));
}

} // namespace duckdb
