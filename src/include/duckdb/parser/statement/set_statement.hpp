//===----------------------------------------------------------------------===//
//                         DuckDB
//
// duckdb/parser/statement/set_statement.hpp
//
//
//===----------------------------------------------------------------------===//

#pragma once

#include "duckdb/common/enums/set_scope.hpp"
#include "duckdb/common/enums/set_type.hpp"
#include "duckdb/parser/sql_statement.hpp"
#include "duckdb/parser/parsed_expression.hpp"

namespace duckdb {

class SetStatement : public SQLStatement {
public:
	static constexpr const StatementType TYPE = StatementType::SET_STATEMENT;

protected:
	SetStatement(Identifier name_p, SetScope scope_p, SetType type_p);
	SetStatement(const SetStatement &other) = default;

public:
	Identifier name;
	SetScope scope;
	SetType set_type;

public:
	void Serialize(Serializer &serializer) const override;
	static unique_ptr<SQLStatement> Deserialize(Deserializer &deserializer);
};

class SetVariableStatement : public SetStatement {
public:
	SetVariableStatement(Identifier name_p, unique_ptr<ParsedExpression> value_p, SetScope scope_p);

protected:
	SetVariableStatement();
	SetVariableStatement(const SetVariableStatement &other);

public:
	unique_ptr<SQLStatement> Copy() const override;
	string ToString() const override;
	void Serialize(Serializer &serializer) const override;
	static unique_ptr<SetStatement> Deserialize(Deserializer &deserializer);

public:
	unique_ptr<ParsedExpression> value;
};

class ResetVariableStatement : public SetStatement {
public:
	ResetVariableStatement(Identifier name_p, SetScope scope_p);

protected:
	ResetVariableStatement();
	ResetVariableStatement(const ResetVariableStatement &other) = default;

public:
	unique_ptr<SQLStatement> Copy() const override;
	string ToString() const override;
	void Serialize(Serializer &serializer) const override;
	static unique_ptr<SetStatement> Deserialize(Deserializer &deserializer);
};

} // namespace duckdb
