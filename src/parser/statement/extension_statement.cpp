#include "duckdb/parser/statement/extension_statement.hpp"
#include "duckdb/common/serializer/serializer.hpp"

namespace duckdb {

void ExtensionStatement::Serialize(Serializer &serializer) const {
	throw SerializationException("Cannot serialize an ExtensionStatement");
}

ExtensionStatement::ExtensionStatement(ParserExtension extension_p, unique_ptr<ParserExtensionParseData> parse_data_p)
    : SQLStatement(StatementType::EXTENSION_STATEMENT), extension(std::move(extension_p)),
      parse_data(std::move(parse_data_p)) {
}

unique_ptr<SQLStatement> ExtensionStatement::Copy() const {
	return make_uniq<ExtensionStatement>(extension, parse_data->Copy());
}

string ExtensionStatement::ToString() const {
	return parse_data->ToString();
}

} // namespace duckdb
