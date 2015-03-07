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

#pragma hdrstop

#include "TCheckedItems.h"
//---------------------------------------------------------------------------
#pragma package(smart_init)

__fastcall TCheckedItems::TCheckedItems()
{
	ItemsList = new TList();
}
//---------------------------------------------------------------------------
__fastcall TCheckedItems::~TCheckedItems()
{
	Clear();

	delete ItemsList;
}
//---------------------------------------------------------------------------

void __fastcall TCheckedItems::Add(TListBoxItem* item)
{
	if (ItemsList->IndexOf(item) < 0)
		ItemsList->Add(item);
}
//---------------------------------------------------------------------------

void __fastcall TCheckedItems::Remove(TListBoxItem* item)
{
	if (ItemsList->IndexOf(item) >= 0)
		ItemsList->Remove(item);
}

//---------------------------------------------------------------------------
void __fastcall TCheckedItems::Clear()
{
	for (int i = 0; i < ItemsList->Count; i++)
	{
		TListBoxItem* lbi 		= (TListBoxItem*)ItemsList->Items[i];
		TCheckBox* lbi_checkbox = (TCheckBox*)lbi->FindStyleResource("check");

		if (lbi_checkbox)
			lbi_checkbox->IsChecked = false;
	}

	ItemsList->Clear();
}
//---------------------------------------------------------------------------

int __fastcall TCheckedItems::IndexOf(TListBoxItem* item)
{
	return ItemsList->IndexOf(item);
}
//---------------------------------------------------------------------------
TListBoxItem* TCheckedItems::GetItem(int index)
{
	return (TListBoxItem*)ItemsList->Items[index];
}

int TCheckedItems::GetCount(void)
{
	return ItemsList->Count;
}

//---------------------------------------------------------------------------

