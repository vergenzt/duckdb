//===----------------------------------------------------------------------===//
//                         DuckDB
//
// duckdb/parser/statement/call_statement.hpp
//
//
//===----------------------------------------------------------------------===//

#pragma once

#include "duckdb/parser/parsed_expression.hpp"
#include "duckdb/parser/sql_statement.hpp"

namespace duckdb {

class CallStatement : public SQLStatement {
public:
	static constexpr const StatementType TYPE = StatementType::CALL_STATEMENT;

public:
	CallStatement();

	unique_ptr<ParsedExpression> function;

protected:
	CallStatement(const CallStatement &other);

public:
	void Serialize(Serializer &serializer) const override;
	static unique_ptr<SQLStatement> Deserialize(Deserializer &deserializer);
	unique_ptr<SQLStatement> Copy() const override;
	string ToString() const override;
};
} // namespace duckdb
