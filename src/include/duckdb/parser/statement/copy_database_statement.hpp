//===----------------------------------------------------------------------===//
//                         DuckDB
//
// duckdb/parser/statement/copy_database_statement.hpp
//
//
//===----------------------------------------------------------------------===//

#pragma once

#include "duckdb/parser/sql_statement.hpp"

namespace duckdb {

enum class CopyDatabaseType : uint8_t { COPY_SCHEMA, COPY_DATA };

class CopyDatabaseStatement : public SQLStatement {
public:
	static constexpr const StatementType TYPE = StatementType::COPY_DATABASE_STATEMENT;

public:
	CopyDatabaseStatement(Identifier from_database, Identifier to_database, CopyDatabaseType copy_type);

	Identifier from_database;
	Identifier to_database;
	CopyDatabaseType copy_type;

protected:
	CopyDatabaseStatement(const CopyDatabaseStatement &other);

public:
	void Serialize(Serializer &serializer) const override;
	static unique_ptr<SQLStatement> Deserialize(Deserializer &deserializer);
	DUCKDB_API unique_ptr<SQLStatement> Copy() const override;
	string ToString() const override;

private:
};
} // namespace duckdb
