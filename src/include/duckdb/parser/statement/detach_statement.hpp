//===----------------------------------------------------------------------===//
//                         DuckDB
//
// duckdb/parser/statement/detach_statement.hpp
//
//
//===----------------------------------------------------------------------===//

#pragma once

#include "duckdb/parser/parsed_data/detach_info.hpp"
#include "duckdb/parser/sql_statement.hpp"

namespace duckdb {

class DetachStatement : public SQLStatement {
public:
	static constexpr const StatementType TYPE = StatementType::DETACH_STATEMENT;

public:
	DetachStatement();

	unique_ptr<DetachInfo> info;

protected:
	DetachStatement(const DetachStatement &other);

public:
	void Serialize(Serializer &serializer) const override;
	static unique_ptr<SQLStatement> Deserialize(Deserializer &deserializer);
	unique_ptr<SQLStatement> Copy() const override;
	string ToString() const override;
};

} // namespace duckdb
