/*---------------------------------------------------------------------------
 *
 * TDBComboBox Class
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

#ifndef TDBComboBoxH
#define TDBComboBoxH
//---------------------------------------------------------------------------
#include <FMX.ListBox.hpp>
#include <Data.DB.hpp>
#include "TCheckedItems.h"

class TDBComboBox : public TComboBox
{
	private:
		bool 			IsMultiselect;
		String 			UserTextInput;

		String 			FDisplayFieldName;
		String			FValueFieldName;

 		TDataSet		*FDataset;
		TTimer			*tmrClearUserTextInput;
		TCheckedItems	*CheckedItemsList;

		char 			FKeyValueSeparator;

		void __fastcall SetMultiselect(bool value);
		void __fastcall tmrClearUserTextInput_OnTimer(TObject *Sender);
		void __fastcall SetKeyValue(String key_value);
		void __fastcall SetDataset(TDataSet* dataset);
		void __fastcall AfterDataSetOpen(TDataSet* DataSet);
		void __fastcall BindData(void);
		void __fastcall SetAlternateRowBackground(bool value);
		void __fastcall OnItemCheckClick(TListBoxItem *item);
		void __fastcall OnItemClick(TListBoxItem *item);

		bool __fastcall GetAlternateRowBackground(void);
		String __fastcall GetKeyValue(void);

	protected:
		virtual void __fastcall KeyDown(System::Word &Key, System::WideChar &KeyChar, System::Classes::TShiftState Shift);
		virtual void __fastcall DoContentPaint(System::TObject* Sender, Fmx::Types::TCanvas* Canvas, const System::Types::TRectF &ARect);
		virtual TComboListBox* __fastcall CreateListBox(void);

		String MORE_ELEMENT_SELECTED_TEXT;
	public:

		__property bool Multiselect 			= {read = IsMultiselect, write = SetMultiselect};
		__property TCheckedItems* CheckedItems 	= {read = CheckedItemsList};
		__property String KeyValue 				= {read = GetKeyValue, write = SetKeyValue};
		__property String DisplayFieldName 		= {read = FDisplayFieldName, write = FDisplayFieldName};
		__property String ValueFieldName  		= {read = FValueFieldName, write = FValueFieldName};
		__property TDataSet* Dataset 			= {read = FDataset, write = SetDataset};
		__property char KeyValueSeparator 		= {read = FKeyValueSeparator, write = FKeyValueSeparator};
		__property bool AlternateRowBackground 	= {read = GetAlternateRowBackground, write = SetAlternateRowBackground};

		__fastcall TDBComboBox(TComponent *Owner);
		__fastcall ~TDBComboBox();

		void __fastcall Clear(void);

};
#endif
