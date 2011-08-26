/*
 * Copyright (C) 2011 Tommi Maekitalo
 *
 * This program is free software; you can redistribute it and/or
 * modify it under the terms of the GNU General Public License as
 * published by the Free Software Foundation; either version 2 of the
 * License, or (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful, but
 * is provided AS IS, WITHOUT ANY WARRANTY; without even the implied
 * warranty of MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE, and
 * NON-INFRINGEMENT.  See the GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program; if not, write to the Free Software
 * Foundation, Inc., 51 Franklin St, Fifth Floor, Boston, MA  02110-1301 USA
 *
 */

#ifndef TNTDB_ROWREADER_H
#define TNTDB_ROWREADER_H

#include <tntdb/bits/row.h>

namespace tntdb
{
  class RowReader
  {
      const Row& row;
      Row::size_type field_num;

    public:
      explicit RowReader(const Row& row_, Row::size_type field_num_ = 0) 
        : row(row_),
          field_num(field_num_)
      { }

      template <typename T>
      RowReader& get(T& ret)
      { row[field_num++].get(ret); return *this; }

      template <typename T>
      RowReader& get(T& ret, bool& nullInd)
      { nullInd = row[field_num++].get(ret); return *this; }

      bool isNull()
      { return row[field_num].isNull(); }

      void rewind(Row::size_type n_ = 0)
      { field_num = 0; }

      const Row& currentRow() const
      { return row; }

      Row::size_type currentCol() const
      { return field_num; }

      Row::size_type operator* () const
      { return field_num; }

      Row::size_type operator++ ()
      { return ++field_num; }

      Row::size_type operator++ (int)
      { return field_num++; }

      Row::size_type operator-- ()
      { return --field_num; }

      Row::size_type operator-- (int)
      { return field_num--; }

  };

  inline RowReader Row::reader(Row::size_type n) const
  { return RowReader(*this, n); }

}

#endif // TNTDB_ROWREADER_H
