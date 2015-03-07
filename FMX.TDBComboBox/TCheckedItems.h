/*---------------------------------------------------------------------------
 *
 * TCheckedItems
 * This file is part of TDBComboBox Class
 *
 * Copyright (C) 2015 Stefano BARILETTI <hackaroth@gmail.com>
 *
 * This program is free software; you can redistribute it and/or
 * modify it under the terms of the GNU General Public License
 * as published by the Free Software Foundation; either version 2
 * of the License, or (at your option) any later version.

 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.

 * You should have received a copy of the GNU General Public License
 * along with this program; if not, write to the Free Software
 * Foundation, Inc., 51 Franklin Street, Fifth Floor, Boston, MA  02110-1301, USA.
 
//---------------------------------------------------------------------------*/

#ifndef TCheckedItemsH
#define TCheckedItemsH
//---------------------------------------------------------------------------
#include <System.Classes.hpp>
#include <FMX.ListBox.hpp>

class TCheckedItems
{
	private:
		TList* ItemsList;

		TListBoxItem* GetItem(int index);
		int GetCount(void);
	public:

		__fastcall TCheckedItems();
		__fastcall ~TCheckedItems();

		void __fastcall Add(TListBoxItem* item);
		void __fastcall Remove(TListBoxItem* item);
		void __fastcall Clear();

		int __fastcall IndexOf(TListBoxItem* item);

		__property TListBoxItem* Items[int index] = {read = GetItem};
		__property int Count = {read = GetCount};

};
#endif
