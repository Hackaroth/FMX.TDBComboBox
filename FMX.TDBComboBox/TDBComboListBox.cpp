/*---------------------------------------------------------------------------
 *
 * TDBComboListBox
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

#include "TDBComboListBox.h"
//---------------------------------------------------------------------------
#pragma package(smart_init)

__fastcall TDBComboListBox::TDBComboListBox(TComponent* Owner) : TComboListBox(Owner)
{
	OnItemClick			= NULL;
	OnItemCheckClick   	= NULL;
}
//---------------------------------------------------------------------------
void __fastcall TDBComboListBox::DoItemApplyLookup(TObject* Object)
{
	TListBoxItem* lbi 	= (TListBoxItem*)Object;
	lbi->OnClick		= DoItemCheckClick;

	TCheckBox* cb 		= (TCheckBox*)lbi->FindStyleResource("check");

	if (cb != NULL)
	{
		cb->OnClick 	= DoItemCheckClick;
		cb->OnDblClick 	= DoItemCheckClick;
	}
}
//---------------------------------------------------------------------------
void __fastcall TDBComboListBox::DoItemCheckClick(TObject* Object)
{
	TListBoxItem* lbi = NULL;

	if (Object->ClassName() == "TListBoxItem" || Object->ClassName() == "TDBListBoxItem")
	{
		lbi  = (TListBoxItem*)Object;

		if (OnItemClick)
       		OnItemClick(lbi);
    }
	if (Object->ClassName() == "TCheckBox")
	{
		lbi  = (TListBoxItem*)((TCheckBox*)Object)->Parent->Parent;

		if (lbi && OnItemCheckClick)
			OnItemCheckClick(lbi);
	}
}
//---------------------------------------------------------------------------

void __fastcall TDBComboListBox::DoAddObject(Fmx::Types::TFmxObject* const AObject)
{
	TComboListBox::DoAddObject(AObject);

	if (AObject->ClassName() == "TListBoxItem" || AObject->ClassName() == "TDBListBoxItem")
	{
		TListBoxItem* lbi 		= (TListBoxItem*)AObject;
		lbi->OnApplyStyleLookup = DoItemApplyLookup;
		lbi->OnClick			= DoItemCheckClick;

		TCheckBox* cb 			= (TCheckBox*)lbi->FindStyleResource("check");

		if (cb != NULL)
		{
			cb->OnClick 		= DoItemCheckClick;
			cb->OnDblClick 		= DoItemCheckClick;
		}
	}
}
//---------------------------------------------------------------------------

void __fastcall TDBComboListBox::SetAlternateBackground(bool value)
{
	AlternatingRowBackground = value;
}
//---------------------------------------------------------------------------

bool __fastcall TDBComboListBox::GetAlternateBackground(void)
{
	return AlternatingRowBackground;
}
//---------------------------------------------------------------------------
void __fastcall TDBComboListBox::SetShowCheckBox(bool value)
{
	ShowCheckboxes  = value;
}
//---------------------------------------------------------------------------

bool __fastcall TDBComboListBox::GetShowCheckBox(void)
{
	return ShowCheckboxes;
}
//---------------------------------------------------------------------------

