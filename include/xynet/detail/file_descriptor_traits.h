//
// Created by xuanyi on 4/28/20.
//

#ifndef XYNET_FILE_DESCRIPTOR_TRAITS_H
#define XYNET_FILE_DESCRIPTOR_TRAITS_H

#include <experimental/type_traits>
#include <tuple>
#include <system_error>

namespace xynet::detail
{

template <typename  T>
concept FileDescriptorPolicy = true;

template <typename T>
using FileDescriptorPolicyUseErrorCodeDetector = typename T::policy_use_error_code;

template <typename T>
concept FileDescriptorPolicyUseErrorCode 
  = std::experimental::is_detected_v<FileDescriptorPolicyUseErrorCodeDetector, T>;

template<FileDescriptorPolicy P, typename... Rs>
struct file_descriptor_operation_return_type;

template <FileDescriptorPolicy P, typename Head, typename... Tail>
struct file_descriptor_operation_return_type<P, Head, Tail...> :
        public std::conditional_t<FileDescriptorPolicyUseErrorCode<P>,
	                          std::tuple<std::error_code, Head, Tail...>,
				  std::tuple<Head, Tail...>>
{
};

template <FileDescriptorPolicy P, typename Head>
struct file_descriptor_operation_return_type<P, Head> :
	public std::conditional_t<FileDescriptorPolicyUseErrorCode<P>,
	                          std::tuple<std::error_code, Head>,
				  Head>
{
};

template <FileDescriptorPolicy P>
struct file_descriptor_operation_return_type<P> :
	public std::conditional_t<FileDescriptorPolicyUseErrorCode<P>,
	                          std::error_code,
				  void>
{
};

template <FileDescriptorPolicy P, typename... Rs>
using file_descriptor_operation_return_type_t = file_descriptor_operation_return_type<P, Rs...>;

}

#endif //XYNET_FILE_DESCRIPTOR_TRAITS_H
