//===----------------------------------------------------------------------===//
//                         DuckDB
//
// duckdb/parser/statement/create_statement.hpp
//
//
//===----------------------------------------------------------------------===//

#pragma once

#include "duckdb/parser/parsed_data/create_info.hpp"
#include "duckdb/parser/sql_statement.hpp"

namespace duckdb {

class CreateStatement : public SQLStatement {
public:
	static constexpr const StatementType TYPE = StatementType::CREATE_STATEMENT;

public:
	CreateStatement();

	unique_ptr<CreateInfo> info;

protected:
	CreateStatement(const CreateStatement &other);

public:
	void Serialize(Serializer &serializer) const override;
	static unique_ptr<SQLStatement> Deserialize(Deserializer &deserializer);
	unique_ptr<SQLStatement> Copy() const override;
	string ToString() const override;
};

} // namespace duckdb
