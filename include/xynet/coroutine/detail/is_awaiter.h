//
// Created by xuanyi on 4/22/20.
//

/*
 * Copyright 2017 Lewis Baker
 *
 * Permission is hereby granted, free of charge, to any person obtaining a copy
 * of this software and associated documentation files (the "Software"), to deal
 * in the Software without restriction, including without limitation the rights
 * to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
 * copies of the Software, and to permit persons to whom the Software is furnished
 * to do so, subject to the following conditions:

 * The above copyright notice and this permission notice shall be included in all
 * copies or substantial portions of the Software.

 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 * IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 * FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
 * AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
 * LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
 * OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
 * SOFTWARE.
 */

#ifndef XYNET_COROUTINE_DETAIL_IS_AWAITER_H
#define XYNET_COROUTINE_DETAIL_IS_AWAITER_H

#include <type_traits>
#include <coroutine>

namespace xynet::detail
{
template<typename T>
struct is_coroutine_handle
  : std::false_type
{};

template<typename PROMISE>
struct is_coroutine_handle<std::coroutine_handle<PROMISE>>
  : std::true_type
{};

template<typename T>
concept is_valid_await_suspend_return_value =
  std::is_void_v<T> || std::is_same_v<T, bool> || is_coroutine_handle<T>::value;

template<typename T>
concept is_awaiter = requires (T t) {
	{ t.await_ready() } -> std::convertible_to<bool>;
	{ t.await_resume() };
	{ t.await_suspend(std::declval<std::coroutine_handle<>>()) } -> is_valid_await_suspend_return_value;
};

}

#endif //XYNET_IS_AWAITER_H
