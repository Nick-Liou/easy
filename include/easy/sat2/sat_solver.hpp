/* easy: C++ ESOP library
 * Copyright (C) 2018  EPFL
 *
 * Permission is hereby granted, free of charge, to any person
 * obtaining a copy of this software and associated documentation
 * files (the "Software"), to deal in the Software without
 * restriction, including without limitation the rights to use,
 * copy, modify, merge, publish, distribute, sublicense, and/or sell
 * copies of the Software, and to permit persons to whom the
 * Software is furnished to do so, subject to the following
 * conditions:
 *
 * The above copyright notice and this permission notice shall be
 * included in all copies or substantial portions of the Software.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND,
 * EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES
 * OF MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND
 * NONINFRINGEMENT. IN NO EVENT SHALL THE AUTHORS OR COPYRIGHT
 * HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY,
 * WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING
 * FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR
 * OTHER DEALINGS IN THE SOFTWARE.
 */

#pragma once

#include <easy/utils/dynamic_bitset.hpp>
#include <iostream>

namespace easy::sat2
{

/*! \brief Satisfying model (or assignment)
 *
 * A vector of bits obtained from a SAT-solver.  The bit at index 0,
 * 1, 2, and so forth corresponds to the variable with ids 1, 2, 3,
 * and so forth.
 *
 */
class model
{
public:
  /*! \brief Default constructor
   *
   * This constructor creates an empty model.
   */
  explicit model() = default;

  /*! \brief Constructor from dynamic_bitset
   *
   * This constructor creates an empty model.
   */
  explicit model( utils::dynamic_bitset<> const& bs )
    : _assignment( bs )
  {}

  /*! \brief Size of model
   *
   * Returns the size of the model.
   */
  uint64_t size() const
  {
    return _assignment.num_bits();
  }

  /*! \brief Get value of a literal.
   *
   * Returns the value of a literal in the model.
   */
  bool operator[]( int lit ) const
  {
    assert( lit != 0 );
    auto const var = abs( lit ) - 1;
    assert( var < _assignment.num_bits() && "Index out-of-bounds access" );
    return lit > 0 ? _assignment[var] : !_assignment[var];
  }

  void print( std::ostream& os = std::cout )
  {
    auto const size = _assignment.num_bits();
    for ( auto i = 0u; i < size; ++i )
    {
      os << _assignment[i];
    }
    os << '\n';
    os.flush();
  }

protected:
  utils::dynamic_bitset<> _assignment;
}; /* model */

/*! \brief Unsatisfiable core
 *
 * A sorted vector of assumption literals that together with the hard
 * clauses of the SAT-solver cannot be satisfied.
 *
 * In general, the core is not minimal.
 */
class core
{
public:
  /*! \brief Default constructor

  This constructor creates an empty core.
  */
  explicit core() = default;

  uint64_t size() const
  {
    return _conflict.size();
  }

protected:
  std::vector<int> _conflict;
}; /* core */

} /* namespace easy::sat2 */
