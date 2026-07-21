#include "duckdb/parser/statement/relation_statement.hpp"
#include "duckdb/main/relation/query_relation.hpp"
#include "duckdb/common/serializer/serializer.hpp"

namespace duckdb {

void RelationStatement::Serialize(Serializer &serializer) const {
	throw SerializationException("Cannot serialize a RelationStatement");
}

RelationStatement::RelationStatement(shared_ptr<Relation> relation_p)
    : SQLStatement(StatementType::RELATION_STATEMENT), relation(std::move(relation_p)) {
	query = relation->GetQuery();
}

unique_ptr<SQLStatement> RelationStatement::Copy() const {
	return unique_ptr<RelationStatement>(new RelationStatement(*this));
}

string RelationStatement::ToString() const {
	return relation->ToString();
}

} // namespace duckdb
