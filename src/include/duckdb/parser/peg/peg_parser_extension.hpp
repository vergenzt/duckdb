//===----------------------------------------------------------------------===//
//                         DuckDB
//
// duckdb/parser/peg/peg_parser_extension.hpp
//
//
//===----------------------------------------------------------------------===//

#pragma once

#include "duckdb/common/common.hpp"
#include "duckdb/common/vector.hpp"
#include "duckdb/parser/peg/transformer/parse_result.hpp"
#include "duckdb/parser/peg/transformer/transform_result.hpp"
#include <functional>

namespace duckdb {
class PEGTransformer;

//! Turns a matched parse result into a DuckDB AST node, wrapped as a TransformResultValue
//! (build the result with make_uniq<TypedTransformResult<unique_ptr<T>>>(...)).
using PEGTransformFunction = std::function<unique_ptr<TransformResultValue>(PEGTransformer &, ParseResult &)>;

//! Splices `alternative_rule` into an existing choice rule so the new syntax becomes reachable.
struct PEGChoiceExtension {
	string target_rule;      //! existing ordered-choice rule, e.g. "Statement" or "SingleExpression"
	string alternative_rule; //! a rule (defined in the extension's grammar) to add as a new alternative
};

//! Teaches the PEG parser new syntax at runtime: extra grammar rules, where to hook them into the
//! core grammar, and how to transform them into AST nodes. Registered by extensions.
struct PEGParserExtension {
	string grammar;                                          //! PEG rules defining the new syntax
	vector<PEGChoiceExtension> choice_extensions;            //! hooks into core choice rules
	vector<pair<string, PEGTransformFunction>> transformers; //! rule_name -> handler
};

//! Process-global registry of parser extensions.
//!
//! It is deliberately global rather than per-DBConfig: a standalone Parser() (e.g. the one
//! json_serialize_sql constructs) has no database handle, so a per-config registry would be
//! invisible there. The matcher and transformer caches consult this when they are (re)built.
class PEGParserExtensionRegistry {
public:
	DUCKDB_API static PEGParserExtensionRegistry &Get();

	//! Register a parser extension.
	//! ponytail: registration is expected before the first parse — already-built caches are not
	//! retroactively invalidated. Fine for load-time registration; the upgrade path is a version
	//! counter checked by ParserCache. Extensions are never removed.
	DUCKDB_API void Register(PEGParserExtension extension);

	//! Stable reference to the registered extensions (valid as long as registration precedes parsing;
	//! matcher token views point into these strings, so they must outlive the cached matcher).
	const vector<PEGParserExtension> &GetExtensions() const {
		return extensions;
	}

private:
	vector<PEGParserExtension> extensions;
};

} // namespace duckdb
