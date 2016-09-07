/*
 * Copyright 2016 Facebook, Inc.
 *
 * Licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 *   http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 */

#include <thrift/test/gen-cpp2/reflection_fatal_struct.h>

#include <thrift/lib/cpp2/fatal/internal/test_helpers.h>

#include <gtest/gtest.h>

FATAL_S(my_structAs, "my_structA");
FATAL_S(field_as, "a");
FATAL_S(field_bs, "b");

template <apache::thrift::field_id_t Id>
using field_id = std::integral_constant<apache::thrift::field_id_t, Id>;

template <apache::thrift::optionality Optionality>
using required = std::integral_constant<
  apache::thrift::optionality,
  Optionality
>;

namespace test_cpp2 {
namespace cpp_reflection {

TEST(fatal_typedef, my_structA_sanity_check) {
  using traits = apache::thrift::reflect_struct<my_structA>;

  EXPECT_SAME<my_structA, traits::type>();
  EXPECT_SAME<my_structAs, traits::name>();
  EXPECT_SAME<reflection_tags::module, traits::module>();

  EXPECT_SAME<field_as, traits::member::a::name>();
  EXPECT_SAME<field_bs, traits::member::b::name>();

  my_structA pod;
  pod.a = 98;
  pod.b = "test";

  EXPECT_EQ(pod.a, traits::member::a::getter::ref(pod));
  EXPECT_EQ(pod.b, traits::member::b::getter::ref(pod));

  traits::member::a::getter::ref(pod) = 98;
  EXPECT_EQ(98, pod.a);

  traits::member::b::getter::ref(pod) = "test";
  EXPECT_EQ("test", pod.b);

  EXPECT_SAME<field_as, fatal::map_get<traits::members, field_as>::name>();
  EXPECT_SAME<field_bs, fatal::map_get<traits::members, field_bs>::name>();

  EXPECT_SAME<std::int32_t, fatal::map_get<traits::members, field_as>::type>();
  EXPECT_SAME<std::string, fatal::map_get<traits::members, field_bs>::type>();

  EXPECT_SAME<field_id<1>, fatal::map_get<traits::members, field_as>::id>();
  EXPECT_SAME<field_id<2>, fatal::map_get<traits::members, field_bs>::id>();

  EXPECT_SAME<
    required<apache::thrift::optionality::required>,
    fatal::map_get<traits::members, field_as>::optional
  >();
  EXPECT_SAME<
    required<apache::thrift::optionality::required>,
    fatal::map_get<traits::members, field_bs>::optional
  >();

  EXPECT_EQ(
    98,
    (fatal::map_get<
        traits::members,
        traits::member::a::name
      >::getter::ref(pod))
  );
  EXPECT_EQ(
    "test",
    ( fatal::map_get<
        traits::members,
        traits::member::b::name
      >::getter::ref(pod))
  );

  EXPECT_SAME<
    apache::thrift::type_class::integral,
    fatal::map_get<traits::members, field_as>::type_class
  >();
  EXPECT_SAME<
    apache::thrift::type_class::string,
    fatal::map_get<traits::members, field_bs>::type_class
  >();

  EXPECT_SAME<
    std::int32_t,
    decltype(
      std::declval<fatal::map_get<traits::members, field_as>::pod<>>().a
    )
  >();
  EXPECT_SAME<
    std::string,
    decltype(
      std::declval<fatal::map_get<traits::members, field_bs>::pod<>>().b
    )
  >();

  EXPECT_SAME<
    bool,
    decltype(
      std::declval<fatal::map_get<traits::members, field_as>::pod<bool>>().a
    )
  >();
  EXPECT_SAME<
    bool,
    decltype(
      std::declval<fatal::map_get<traits::members, field_bs>::pod<bool>>().b
    )
  >();

  EXPECT_SAME<
    traits::member::a,
    fatal::map_get<traits::members, traits::member::a::name>
  >();
  EXPECT_SAME<
    traits::member::b,
    fatal::map_get<traits::members, traits::member::b::name>
  >();
}

TEST(fatal_typedef, annotations) {
  EXPECT_SAME<
    fatal::map<>,
    apache::thrift::reflect_struct<my_structA>::annotations::map
  >();
}

TEST(fatal_typedef, member_annotations) {
  using info = apache::thrift::reflect_struct<my_structA>;

  EXPECT_SAME<fatal::map<>, info::members_annotations::a::map>();
  EXPECT_SAME<fatal::map<>, info::members_annotations::b::map>();
}

TEST(fatal_typedef, is_set_methods) {
  using info = apache::thrift::reflect_struct<my_structA>;
  using field_a = fatal::map_get<info::members, info::member::a::name>;
  using field_b = fatal::map_get<info::members, info::member::b::name>;

  my_structA pod;

  EXPECT_EQ(true, field_a::is_set(pod));
  field_a::mark_set(pod);
  EXPECT_EQ(true, field_a::is_set(pod));

  EXPECT_EQ(true, field_b::is_set(pod));
  field_b::mark_set(pod);
  EXPECT_EQ(true, field_b::is_set(pod));
}

} // namespace cpp_reflection {
} // namespace test_cpp2 {
