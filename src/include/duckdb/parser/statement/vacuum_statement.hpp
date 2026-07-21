//===----------------------------------------------------------------------===//
//                         DuckDB
//
// duckdb/parser/statement/vacuum_statement.hpp
//
//
//===----------------------------------------------------------------------===//

#pragma once

#include "duckdb/parser/sql_statement.hpp"
#include "duckdb/parser/parsed_data/vacuum_info.hpp"

namespace duckdb {

class VacuumStatement : public SQLStatement {
public:
	static constexpr const StatementType TYPE = StatementType::VACUUM_STATEMENT;

public:
	VacuumStatement();
	explicit VacuumStatement(const VacuumOptions &options);

	unique_ptr<VacuumInfo> info;

protected:
	VacuumStatement(const VacuumStatement &other);

public:
	void Serialize(Serializer &serializer) const override;
	static unique_ptr<SQLStatement> Deserialize(Deserializer &deserializer);
	unique_ptr<SQLStatement> Copy() const override;
	string ToString() const override;
};

} // namespace duckdb
