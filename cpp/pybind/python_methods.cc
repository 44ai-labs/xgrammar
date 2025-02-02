/*!
 *  Copyright (c) 2024 by Contributors
 * \file xgrammar/grammar.cc
 */

#include "python_methods.h"

#include <xgrammar/xgrammar.h>

#include <algorithm>
#include <chrono>
#include <cstdint>
#include <iostream>
#include <vector>

#include "../support/dynamic_bitset.h"
#include "../support/logging.h"

namespace xgrammar {

TokenizerInfo TokenizerInfo_Init(
    const std::vector<std::string>& encoded_vocab,
    std::string vocab_type,
    std::optional<int> vocab_size,
    std::optional<std::vector<int32_t>> stop_token_ids,
    bool prepend_space_in_tokenization
) {
  const std::unordered_map<std::string, VocabType> VOCAB_TYPE_MAP = {
      {"RAW", VocabType::RAW},
      {"BYTE_FALLBACK", VocabType::BYTE_FALLBACK},
      {"BYTE_LEVEL", VocabType::BYTE_LEVEL},
  };
  XGRAMMAR_CHECK(VOCAB_TYPE_MAP.count(vocab_type)) << "Invalid vocab type: " << vocab_type;
  return TokenizerInfo(
      encoded_vocab,
      VOCAB_TYPE_MAP.at(vocab_type),
      vocab_size,
      stop_token_ids,
      prepend_space_in_tokenization
  );
}

std::string TokenizerInfo_GetVocabType(const TokenizerInfo& tokenizer) {
  const std::string VOCAB_TYPE_NAMES[] = {"RAW", "BYTE_FALLBACK", "BYTE_LEVEL"};
  return VOCAB_TYPE_NAMES[static_cast<int>(tokenizer.GetVocabType())];
}

std::vector<pybind11::bytes> TokenizerInfo_GetDecodedVocab(const TokenizerInfo& tokenizer) {
  const auto& decoded_vocab = tokenizer.GetDecodedVocab();
  std::vector<pybind11::bytes> py_result;
  py_result.reserve(decoded_vocab.size());
  for (const auto& item : decoded_vocab) {
    py_result.emplace_back(pybind11::bytes(item));
  }
  return py_result;
}

void GrammarMatcher_FillNextTokenBitmask(
    GrammarMatcher& matcher, intptr_t token_bitmask_ptr, std::vector<int64_t> shape, int32_t index
) {
  XGRAMMAR_CHECK(shape.size() == 1 || shape.size() == 2) << "token_bitmask tensor must be 1D or 2D";

  DLTensor bitmask_dltensor{
      reinterpret_cast<void*>(token_bitmask_ptr),
      DLDevice{kDLCPU, 0},
      static_cast<int32_t>(shape.size()),
      GetBitmaskDLType(),
      shape.data(),
      nullptr,
      0
  };
  matcher.FillNextTokenBitmask(&bitmask_dltensor, index);
}

std::vector<int> Matcher_DebugGetMaskedTokensFromBitmask(
    intptr_t token_bitmask_ptr, std::vector<int64_t> shape, int32_t vocab_size, int32_t index
) {
  XGRAMMAR_CHECK(shape.size() == 1 || shape.size() == 2) << "token_bitmask tensor must be 1D or 2D";

  DLTensor bitmask_dltensor{
      reinterpret_cast<void*>(token_bitmask_ptr),
      DLDevice{kDLCPU, 0},
      static_cast<int32_t>(shape.size()),
      GetBitmaskDLType(),
      shape.data(),
      nullptr,
      0
  };

  std::vector<int> result;
  _DebugGetMaskedTokensFromBitmask(&result, bitmask_dltensor, vocab_size, index);
  return result;
}

}  // namespace xgrammar
