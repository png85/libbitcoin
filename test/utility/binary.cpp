/**
 * Copyright (c) 2011-2015 libbitcoin developers (see AUTHORS)
 *
 * This file is part of libbitcoin.
 *
 * libbitcoin is free software: you can redistribute it and/or modify
 * it under the terms of the GNU Affero General Public License with
 * additional permissions to the one published by the Free Software
 * Foundation, either version 3 of the License, or (at your option)
 * any later version. For more information see LICENSE.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU Affero General Public License for more details.
 *
 * You should have received a copy of the GNU Affero General Public License
 * along with this program. If not, see <http://www.gnu.org/licenses/>.
 */
#include <boost/test/unit_test.hpp>
#include <bitcoin/bitcoin.hpp>

using namespace bc;

BOOST_AUTO_TEST_SUITE(binary_tests)

BOOST_AUTO_TEST_SUITE(binary__to_string)

BOOST_AUTO_TEST_CASE(prefix_to_string__32_bits__expected_value)
{
    const data_chunk blocks{ { 0xba, 0xad, 0xf0, 0x0d } };
    const binary_type prefix(32, blocks);
    std::stringstream stream;
    stream << prefix;
    BOOST_REQUIRE_EQUAL(stream.str(), "10111010101011011111000000001101");
}

BOOST_AUTO_TEST_SUITE_END()

BOOST_AUTO_TEST_SUITE(binary__shift_left)

BOOST_AUTO_TEST_CASE(shift_left_by_zero)
{
    binary_type::size_type distance = 0;
    binary_type instance(16, data_chunk { 0xAA, 0xAA, 0xAA });
    binary_type expected(16, data_chunk { 0xAA, 0xAA });
    instance.shift_left(distance);
    BOOST_REQUIRE(expected == instance);
}

BOOST_AUTO_TEST_CASE(shift_left_alternate_initial)
{
    binary_type::size_type distance = 16;
    binary_type instance(24, data_chunk { 0xAB, 0xCD, 0xEF });
    binary_type expected(8, data_chunk { 0xEF });
    instance.shift_left(distance);
    BOOST_REQUIRE(expected == instance);
}

BOOST_AUTO_TEST_CASE(shift_left_by_less_than_byte)
{
    binary_type::size_type distance = 5;
    binary_type instance(24, data_chunk { 0xAA, 0xAA, 0xAA });
    binary_type expected(19, data_chunk { 0x55, 0x55, 0x40});
    instance.shift_left(distance);
    BOOST_REQUIRE(expected == instance);
}

BOOST_AUTO_TEST_CASE(shift_left_by_less_than_byte_to_byte_align)
{
    binary_type::size_type distance = 5;
    binary_type instance(21, data_chunk { 0xAA, 0xAA, 0xAA });
    binary_type expected(16, data_chunk { 0x55, 0x55 });
    instance.shift_left(distance);
    BOOST_REQUIRE(expected == instance);
}

BOOST_AUTO_TEST_CASE(shift_left_by_byte_single)
{
    binary_type::size_type distance = 8;
    binary_type instance(24, data_chunk { 0xAA, 0xAA, 0xAA });
    binary_type expected(16, data_chunk { 0xAA, 0xAA });
    instance.shift_left(distance);
    BOOST_REQUIRE(expected == instance);
}

BOOST_AUTO_TEST_CASE(shift_left_by_greater_than_byte)
{
    binary_type::size_type distance = 13;
    binary_type instance(24, data_chunk { 0xAA, 0xAA, 0xAA });
    binary_type expected(11, data_chunk { 0x55, 0x40 });
    instance.shift_left(distance);
    BOOST_REQUIRE(expected == instance);
}

BOOST_AUTO_TEST_CASE(shift_left_by_greater_than_byte_not_initially_aligned)
{
    binary_type::size_type distance = 13;
    binary_type instance(18, data_chunk { 0xAA, 0xAA, 0xAA });
    binary_type expected(5, data_chunk { 0x50 });
    instance.shift_left(distance);
    BOOST_REQUIRE(expected == instance);
}

BOOST_AUTO_TEST_CASE(shift_left_by_byte_multiple)
{
    binary_type::size_type distance = 16;
    binary_type instance(24, data_chunk { 0xAA, 0xAA, 0xAA });
    binary_type expected(8, data_chunk { 0xAA });
    instance.shift_left(distance);
    BOOST_REQUIRE(expected == instance);
}

BOOST_AUTO_TEST_CASE(shift_left_by_size)
{
    binary_type::size_type distance = 24;
    binary_type instance(24, data_chunk { 0xAA, 0xAA, 0xAA });
    binary_type expected(0, data_chunk { });
    instance.shift_left(distance);
    BOOST_REQUIRE(expected == instance);
}

BOOST_AUTO_TEST_CASE(shift_left_by_greater_than_size)
{
    binary_type::size_type distance = 30;
    binary_type instance(24, data_chunk { 0xAA, 0xAA, 0xAA });
    binary_type expected(0, data_chunk { });
    instance.shift_left(distance);
    BOOST_REQUIRE(expected == instance);
}

BOOST_AUTO_TEST_SUITE_END()

BOOST_AUTO_TEST_SUITE(binary__shift_right)

BOOST_AUTO_TEST_CASE(shift_right_by_zero)
{
    binary_type::size_type distance = 0;
    binary_type instance(16, data_chunk { 0xAA, 0xAA, 0xAA });
    binary_type expected(16, data_chunk { 0xAA, 0xAA });
    instance.shift_right(distance);
    BOOST_REQUIRE(expected == instance);
}

BOOST_AUTO_TEST_CASE(shift_right_by_less_than_byte)
{
    binary_type::size_type distance = 5;
    binary_type instance(24, data_chunk { 0xAA, 0xAA, 0xAA });
    binary_type expected(29, data_chunk { 0x05, 0x55, 0x55, 0x50});
    instance.shift_right(distance);
    BOOST_REQUIRE(expected == instance);
}

BOOST_AUTO_TEST_CASE(shift_right_by_less_than_byte_to_byte_align)
{
    binary_type::size_type distance = 3;
    binary_type instance(21, data_chunk { 0xAA, 0xAA, 0xAA });
    binary_type expected(24, data_chunk { 0x15, 0x55, 0x55 });
    instance.shift_right(distance);
    BOOST_REQUIRE(expected == instance);
}

BOOST_AUTO_TEST_CASE(shift_right_by_byte_single)
{
    binary_type::size_type distance = 8;
    binary_type instance(24, data_chunk { 0xAA, 0xAA, 0xAA });
    binary_type expected(32, data_chunk { 0x00, 0xAA, 0xAA, 0xAA });
    instance.shift_right(distance);
    BOOST_REQUIRE(expected == instance);
}

BOOST_AUTO_TEST_CASE(shift_right_by_greater_than_byte)
{
    binary_type::size_type distance = 13;
    binary_type instance(24, data_chunk { 0xAA, 0xAA, 0xAA });
    binary_type expected(37, data_chunk { 0x00, 0x05, 0x55, 0x55, 0x50 });
    instance.shift_right(distance);
    BOOST_REQUIRE(expected == instance);
}

BOOST_AUTO_TEST_CASE(shift_right_by_greater_than_byte_not_initially_aligned)
{
    binary_type::size_type distance = 13;
    binary_type instance(18, data_chunk { 0xAA, 0xAA, 0xAA });
    binary_type expected(31, data_chunk { 0x00, 0x05, 0x55, 0x54 });
    instance.shift_right(distance);
    BOOST_REQUIRE(expected == instance);
}

BOOST_AUTO_TEST_CASE(shift_right_by_byte_multiple)
{
    binary_type::size_type distance = 16;
    binary_type instance(24, data_chunk { 0xAA, 0xAA, 0xAA });
    binary_type expected(40, data_chunk { 0x00, 0x00, 0xAA, 0xAA, 0xAA });
    instance.shift_right(distance);
    BOOST_REQUIRE(expected == instance);
}

BOOST_AUTO_TEST_CASE(shift_right_by_size)
{
    binary_type::size_type distance = 24;
    binary_type instance(24, data_chunk { 0xAA, 0xAA, 0xAA });
    binary_type expected(48, data_chunk { 0x00, 0x00, 0x00, 0xAA, 0xAA, 0xAA });
    instance.shift_right(distance);
    BOOST_REQUIRE(expected == instance);
}

BOOST_AUTO_TEST_CASE(shift_right_by_greater_than_size)
{
    binary_type::size_type distance = 30;
    binary_type instance(24, data_chunk { 0xAA, 0xAA, 0xAA });
    binary_type expected(54, data_chunk { 0x00, 0x00, 0x00, 0x02, 0xAA, 0xAA, 0xA8 });
    instance.shift_right(distance);
    BOOST_REQUIRE(expected == instance);
}

BOOST_AUTO_TEST_SUITE_END()

BOOST_AUTO_TEST_SUITE(binary__append)

BOOST_AUTO_TEST_CASE(append_to_zero_length)
{
    binary_type instance(0, data_chunk { 0x00 });
    binary_type augment(24, data_chunk { 0xAA, 0xBB, 0xCC });
    binary_type expected(24, data_chunk { 0xAA, 0xBB, 0xCC });
    instance.append(augment);
    BOOST_REQUIRE(expected == instance);
}

BOOST_AUTO_TEST_CASE(append_zero_length_to_content)
{
    binary_type instance(24, data_chunk { 0xAA, 0xBB, 0xCC });
    binary_type augment(0, data_chunk { });
    binary_type expected(24, data_chunk { 0xAA, 0xBB, 0xCC });
    instance.append(augment);
    BOOST_REQUIRE(expected == instance);
}

BOOST_AUTO_TEST_CASE(append_byte_aligned_instances)
{
    binary_type instance(24, data_chunk { 0xAA, 0xBB, 0xCC });
    binary_type augment(24, data_chunk { 0xDD, 0xEE, 0xFF });
    binary_type expected(48, data_chunk { 0xAA, 0xBB, 0xCC, 0xDD, 0xEE, 0xFF });
    instance.append(augment);
    BOOST_REQUIRE(expected == instance);
}

BOOST_AUTO_TEST_CASE(append_byte_nonaligned_instances)
{
    binary_type instance(20, data_chunk { 0xAA, 0xBB, 0xCC });
    binary_type augment(13, data_chunk { 0xDD, 0xEE });
    binary_type expected(33, data_chunk { 0xAA, 0xBB, 0xCD, 0xDE, 0x80 });
    instance.append(augment);
    BOOST_REQUIRE(expected == instance);
}

//
// prepend tests
//
BOOST_AUTO_TEST_CASE(prepend_to_zero_length)
{
    binary_type instance(0, data_chunk { 0x00 });
    binary_type augment(24, data_chunk { 0xAA, 0xBB, 0xCC });
    binary_type expected(24, data_chunk { 0xAA, 0xBB, 0xCC });
    instance.prepend(augment);
    BOOST_REQUIRE(expected == instance);
}

BOOST_AUTO_TEST_CASE(prepend_zero_length_to_content)
{
    binary_type instance(24, data_chunk { 0xAA, 0xBB, 0xCC });
    binary_type augment(0, data_chunk { });
    binary_type expected(24, data_chunk { 0xAA, 0xBB, 0xCC });
    instance.prepend(augment);
    BOOST_REQUIRE(expected == instance);
}

BOOST_AUTO_TEST_CASE(prepend_byte_aligned_instances)
{
    binary_type instance(24, data_chunk { 0xAA, 0xBB, 0xCC });
    binary_type augment(24, data_chunk { 0xDD, 0xEE, 0xFF });
    binary_type expected(48, data_chunk { 0xDD, 0xEE, 0xFF, 0xAA, 0xBB, 0xCC });
    instance.prepend(augment);
    BOOST_REQUIRE(expected == instance);
}

BOOST_AUTO_TEST_CASE(prepend_byte_nonaligned_instances)
{
    binary_type instance(20, data_chunk { 0xAA, 0xBB, 0xCC });
    binary_type augment(13, data_chunk { 0xDD, 0xEE });
    binary_type expected(33, data_chunk { 0xDD, 0xED, 0x55, 0xDE, 0x00 });
    instance.prepend(augment);
    BOOST_REQUIRE(expected == instance);
}

BOOST_AUTO_TEST_SUITE_END()

BOOST_AUTO_TEST_SUITE(binary__substring)

BOOST_AUTO_TEST_CASE(substring_start_after_end)
{
    binary_type instance(20, data_chunk { 0xAA, 0xBB, 0xCC });
    binary_type::size_type start = 21;
    binary_type::size_type length = 10;
    binary_type expected(0, data_chunk {});
    binary_type result = instance.substring(start, length);
    BOOST_REQUIRE(expected == result);
}

BOOST_AUTO_TEST_CASE(substring_length_zero)
{
    binary_type instance(20, data_chunk { 0xAA, 0xBB, 0xCC });
    binary_type::size_type start = 5;
    binary_type::size_type length = 0;
    binary_type expected(0, data_chunk {});
    binary_type result = instance.substring(start, length);
    BOOST_REQUIRE(expected == result);
}

BOOST_AUTO_TEST_CASE(substring_byte_aligned_start)
{
    binary_type instance(20, data_chunk { 0xAA, 0xBB, 0xCC });
    binary_type::size_type start = 8;
    binary_type::size_type length = 10;
    binary_type expected(10, data_chunk { 0xBB, 0xC0 });
    binary_type result = instance.substring(start, length);
    BOOST_REQUIRE(expected == result);
}

BOOST_AUTO_TEST_CASE(substring_byte_nonaligned_start)
{
    binary_type instance(20, data_chunk { 0xAA, 0xBB, 0xCC });
    binary_type::size_type start = 10;
    binary_type::size_type length = 10;
    binary_type expected(10, data_chunk { 0xEF, 0x00 });
    binary_type result = instance.substring(start, length);
    BOOST_REQUIRE(expected == result);
}

BOOST_AUTO_TEST_CASE(substring_request_exceeds_string)
{
    binary_type instance(20, data_chunk { 0xAA, 0xBB, 0xCC });
    binary_type::size_type start = 10;
    binary_type::size_type length = 15;
    binary_type expected(10, data_chunk { 0xEF, 0x00 });
    binary_type result = instance.substring(start, length);
    BOOST_REQUIRE(expected == result);
}

BOOST_AUTO_TEST_CASE(substring_implicit_length)
{
    binary_type instance(20, data_chunk { 0xAA, 0xBB, 0xCC });
    binary_type::size_type start = 10;
    binary_type expected(10, data_chunk { 0xEF, 0x00 });
    binary_type result = instance.substring(start);
    BOOST_REQUIRE(expected == result);
}

BOOST_AUTO_TEST_SUITE_END()

BOOST_AUTO_TEST_SUITE(binary__blocks)

BOOST_AUTO_TEST_CASE(string_to_prefix__32_bits__expected_value)
{
    const data_chunk blocks{ { 0xba, 0xad, 0xf0, 0x0d } };
    const binary_type prefix("10111010101011011111000000001101");
    BOOST_REQUIRE(prefix.blocks() == blocks);
}

BOOST_AUTO_TEST_CASE(prefix_to_bytes__32_bits__expected_value)
{
    const data_chunk blocks{ { 0xba, 0xad, 0xf0, 0x0d } };
    const binary_type prefix(32, blocks);
    BOOST_REQUIRE(prefix.blocks() == blocks);
}

BOOST_AUTO_TEST_CASE(bytes_to_prefix__zero_bits__round_trips)
{
    const data_chunk bytes;
    const binary_type prefix(0, bytes);
    std::stringstream stream;
    stream << prefix;
    BOOST_REQUIRE_EQUAL(prefix.size(), 0u);
    BOOST_REQUIRE_EQUAL(prefix.blocks().size(), 0u);
    BOOST_REQUIRE(stream.str().empty());
}

BOOST_AUTO_TEST_CASE(prefix_to_bytes__zero_bits__round_trips)
{
    const data_chunk blocks{ { 0x00, 0x00, 0x00, 0x00 } };
    const binary_type prefix(0, blocks);
    const auto bytes = prefix.blocks();
    std::stringstream stream;
    stream << prefix;
    BOOST_REQUIRE_EQUAL(prefix.size(), 0u);
    BOOST_REQUIRE_EQUAL(prefix.blocks().size(), 0u);
    BOOST_REQUIRE_EQUAL(bytes.size(), 0u);
    BOOST_REQUIRE(stream.str().empty());
}

BOOST_AUTO_TEST_CASE(bytes_to_prefix__one_bit__round_trips)
{
    data_chunk bytes{ { 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF } };
    auto prefix = binary_type(1, bytes);
    std::stringstream stream;
    stream << prefix;
    BOOST_REQUIRE_EQUAL(prefix.size(), 1u);
    BOOST_REQUIRE_EQUAL(prefix.blocks().size(), 1u);
    BOOST_REQUIRE_EQUAL(stream.str(), "1");
}

BOOST_AUTO_TEST_CASE(prefix_to_bytes__one_bit__round_trips)
{
    const data_chunk blocks{ { 0xff, 0xff, 0xff, 0xff } };
    const binary_type prefix(1, blocks);
    const auto bytes = prefix.blocks();
    std::stringstream stream;
    stream << prefix;
    BOOST_REQUIRE_EQUAL(prefix.size(), 1u);
    BOOST_REQUIRE_EQUAL(prefix.blocks().size(), 1u);
    BOOST_REQUIRE_EQUAL(bytes.size(), 1u);
    BOOST_REQUIRE_EQUAL(stream.str(), "1");
}

BOOST_AUTO_TEST_CASE(bytes_to_prefix__two_bits_leading_zero__round_trips)
{
    const data_chunk bytes{ { 0x01, 0x42, 0x42, 0x42, 0x42, 0x42, 0x42, 0x42 } };
    const auto prefix = binary_type(2, bytes);
    std::stringstream stream;
    stream << prefix;
    BOOST_REQUIRE_EQUAL(prefix.size(), 2u);
    BOOST_REQUIRE_EQUAL(prefix.blocks().size(), 1u);
    BOOST_REQUIRE_EQUAL(stream.str(), "00");
}

BOOST_AUTO_TEST_CASE(prefix_to_bytes__two_bits_leading_zero__round_trips)
{
    const data_chunk blocks{ { 0x42, 0x42, 0x42, 0x01 } };
    const binary_type prefix(2, blocks);
    auto bytes = prefix.blocks();
    std::stringstream stream;
    stream << prefix;
    BOOST_REQUIRE_EQUAL(prefix.size(), 2u);
    BOOST_REQUIRE_EQUAL(prefix.blocks().size(), 1u);
    BOOST_REQUIRE_EQUAL(bytes.size(), 1u);
    BOOST_REQUIRE_EQUAL(stream.str(), "01");
}

BOOST_AUTO_TEST_CASE(bytes_to_prefix__two_bytes_leading_null_byte__round_trips)
{
    const data_chunk bytes{ { 0xFF, 0x00 } };
    const auto prefix = binary_type(16, bytes);
    std::stringstream stream;
    stream << prefix;
    BOOST_REQUIRE_EQUAL(prefix.size(), 16u);
    BOOST_REQUIRE_EQUAL(prefix.blocks().size(), 2u);
    BOOST_REQUIRE_EQUAL(stream.str(), "1111111100000000");
}

BOOST_AUTO_TEST_CASE(prefix_to_bytes__two_bytes_leading_null_byte__round_trips)
{
    const data_chunk blocks{ { 0x00, 0x00 } };
    const binary_type prefix(16, blocks);
    auto bytes = prefix.blocks();
    std::stringstream stream;
    stream << prefix;
    BOOST_REQUIRE_EQUAL(prefix.size(), 16u);
    BOOST_REQUIRE_EQUAL(prefix.blocks().size(), 2u);
    BOOST_REQUIRE_EQUAL(bytes.size(), 2u);
    BOOST_REQUIRE_EQUAL(stream.str(), "0000000000000000");
}

BOOST_AUTO_TEST_SUITE_END()

BOOST_AUTO_TEST_SUITE_END()
