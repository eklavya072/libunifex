/*
 * Copyright (c) Facebook, Inc. and its affiliates.
 *
 * Licensed under the Apache License Version 2.0 with LLVM Exceptions
 * (the "License"); you may not use this file except in compliance with
 * the License. You may obtain a copy of the License at
 *
 *   https://llvm.org/LICENSE.txt
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 */

#include <unifex/inplace_stop_token.hpp>

#include <gtest/gtest.h>

namespace {

using namespace unifex;

TEST(inplace_stop_token_test, request_stop_returns_true_if_already_requested) {
  inplace_stop_source source;
  int calls = 0;
  auto onStop = [&]() noexcept {
    ++calls;
  };
  inplace_stop_callback<decltype(onStop)> callback{source.get_token(), onStop};

  EXPECT_FALSE(source.request_stop());
  EXPECT_TRUE(source.stop_requested());
  EXPECT_EQ(calls, 1);

  EXPECT_TRUE(source.request_stop());
  EXPECT_EQ(calls, 1);
}

}  // namespace
