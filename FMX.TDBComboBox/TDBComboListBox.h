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

#ifndef TDBComboListBoxH
#define TDBComboListBoxH
//---------------------------------------------------------------------------
#include <FMX.ListBox.hpp>

typedef void __fastcall (__closure *TListItemCheckClick)(TListBoxItem *item);

class TDBComboListBox : public TComboListBox
{
	protected:
		virtual void __fastcall DoAddObject(Fmx::Types::TFmxObject* const AObject);
	private:
		void __fastcall DoItemApplyLookup(TObject* Object);
		void __fastcall DoItemCheckClick(TObject* Object);
		void __fastcall SetAlternateBackground(bool value);
		void __fastcall SetShowCheckBox(bool value);

		bool __fastcall GetShowCheckBox(void);
		bool __fastcall GetAlternateBackground(void);

	public:

		__fastcall TDBComboListBox(TComponent* Owner);

		__property bool AlternateBackground = {read = GetAlternateBackground, write = SetAlternateBackground};
		__property bool ShowCheckBox		= {read = GetShowCheckBox, write = SetShowCheckBox};

		TListItemCheckClick OnItemCheckClick;
		TListItemCheckClick OnItemClick;


};
#endif
