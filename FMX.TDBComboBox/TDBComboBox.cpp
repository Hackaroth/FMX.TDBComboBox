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

#pragma hdrstop

#include "TDBComboBox.h"
#include "TDBComboListBox.h"
#include "TDBListBoxItem.h"
//---------------------------------------------------------------------------
#pragma package(smart_init)

__fastcall TDBComboBox::TDBComboBox(TComponent *Owner) : TComboBox(Owner)
{
	MORE_ELEMENT_SELECTED_TEXT		= "More elements selected...";

	FDataset						= NULL;
	FDisplayFieldName				= "";
	FValueFieldName					= "";

	IsMultiselect 					= false;

	FKeyValueSeparator				= ';';

	DropDownKind 					= ddkCustom;

	ListBox->ShowScrollBars 		= true;

	CheckedItemsList				= new TCheckedItems();

	tmrClearUserTextInput 			= new TTimer(this);
	tmrClearUserTextInput->Interval = 500;
	tmrClearUserTextInput->Enabled  = false;
	tmrClearUserTextInput->OnTimer  = tmrClearUserTextInput_OnTimer;
}
//---------------------------------------------------------------------------

__fastcall TDBComboBox::~TDBComboBox()
{
	tmrClearUserTextInput->Enabled  = false;
	delete tmrClearUserTextInput;

	CheckedItemsList->Clear();

	delete CheckedItemsList;
}
//---------------------------------------------------------------------------
void __fastcall TDBComboBox::KeyDown(System::Word &Key, System::WideChar &KeyChar, System::Classes::TShiftState Shift)
{
	if (Key == vkReturn)
	{
		OnItemClick(Selected);
		CloseAllPopups();
	}
	else
	{
		tmrClearUserTextInput->Enabled = false;

		UserTextInput += KeyChar;

		int idx = -1;

		for (int i = 0; i < this->Count; i++)
		{
			if (UserTextInput.LowerCase() == this->Items->Strings[i].SubString(1, UserTextInput.Length()).LowerCase())
			{
				idx = i;
				break;
			}
		}

		if (idx >- 1)
			ItemIndex=idx;

		tmrClearUserTextInput->Enabled = true;
	}
}
//---------------------------------------------------------------------------

void __fastcall TDBComboBox::SetMultiselect(bool value)
{
	IsMultiselect = value;

	((TDBComboListBox*)ListBox)->ShowCheckBox = value;

	CheckedItemsList->Clear();
}

//---------------------------------------------------------------------------
bool __fastcall TDBComboBox::GetAlternateRowBackground(void)
{
	return ((TDBComboListBox*)ListBox)->AlternateBackground;
}
//---------------------------------------------------------------------------

void __fastcall TDBComboBox::SetAlternateRowBackground(bool value)
{
	((TDBComboListBox*)ListBox)->AlternateBackground = value;
}
//---------------------------------------------------------------------------
void __fastcall TDBComboBox::tmrClearUserTextInput_OnTimer(TObject *Sender)
{
   tmrClearUserTextInput->Enabled 	= false;
   UserTextInput 					= "";
}

//---------------------------------------------------------------------------
void __fastcall TDBComboBox::DoContentPaint(System::TObject* Sender, Fmx::Types::TCanvas* Canvas, const System::Types::TRectF &ARect)
{
	Canvas->Fill->Color = claBlack;

	if (Multiselect)
	{
		if (CheckedItems->Count > 1)
		{
			Canvas->FillText(ARect, MORE_ELEMENT_SELECTED_TEXT, false, 1, TFillTextFlags(), TTextAlign::taLeading);
		}
		else if (CheckedItems->Count == 1)
		{
			Canvas->FillText(ARect, ((TListBoxItem*)CheckedItems->Items[0])->Text,false,1, TFillTextFlags(), TTextAlign::taLeading);
		}
		else
		{
			if (Selected)
				Canvas->FillText(ARect, Selected->Text, false, 1, TFillTextFlags(), TTextAlign::taLeading);
			else
				Canvas->FillText(ARect, "", false, 1, TFillTextFlags(), TTextAlign::taLeading);
		}
	}
	else
	{
		if (Selected)
			Canvas->FillText(ARect, Selected->Text, false, 1, TFillTextFlags(), TTextAlign::taLeading);
		else
			Canvas->FillText(ARect, "", false, 1, TFillTextFlags(), TTextAlign::taLeading);

	}

}
//---------------------------------------------------------------------------

void __fastcall TDBComboBox::Clear(void)
{
	CheckedItemsList->Clear();
	ItemIndex = -1;
}

//---------------------------------------------------------------------------
void __fastcall TDBComboBox::SetDataset(TDataSet* dataset)
{
	FDataset = dataset;

	if (FDataset == NULL)
	{
		Clear();
		Items->Clear();
	}
	else
	{
		FDataset->AfterOpen  	= AfterDataSetOpen;
		FDataset->AfterRefresh  = AfterDataSetOpen;

		if (FDataset->Active)
			BindData();
	}
}
//---------------------------------------------------------------------------
void __fastcall TDBComboBox::BindData(void)
{
	if (!FDisplayFieldName.IsEmpty())
	{
		Clear();
		Items->Clear();

		FDataset->First();

		while (!FDataset->Eof)
		{
			TDBListBoxItem* lbi	= new TDBListBoxItem(ListBox);
			lbi->Text 			= FDataset->FieldByName(FDisplayFieldName)->AsString;

			if (!FValueFieldName.IsEmpty())
				lbi->Key = FDataset->FieldByName(FValueFieldName)->AsString;

			lbi->Parent = ListBox;

			FDataset->Next();
        }
	}
}
//---------------------------------------------------------------------------

void __fastcall TDBComboBox::AfterDataSetOpen(TDataSet* DataSet)
{
	BindData();
}
//---------------------------------------------------------------------------

String __fastcall TDBComboBox::GetKeyValue(void)
{
	String res = "";

	if (FDataset != NULL)
	{
		if (Multiselect)
		{
			if (CheckedItems->Count > 0)
			{
				for (int i = 0; i < CheckedItems->Count; i++)
				{
					if (CheckedItems->Items[i]->ClassName() == "TDBListBoxItem")
					{
						TDBListBoxItem* item = (TDBListBoxItem*)CheckedItems->Items[i];

						if (!item->Key.IsEmpty())
						{
							res += item->Key;

							if (i < CheckedItems->Count - 1)
								res += FKeyValueSeparator;
						}
					}
				}
			}
		}
		else if (Selected && Selected->ClassName() == "TDBListBoxItem")
		{
			TDBListBoxItem* item = (TDBListBoxItem*)Selected;

			if (!item->Key.IsEmpty())
				res = item->Key;
		}
	}

	return res;
}
//---------------------------------------------------------------------------
void __fastcall TDBComboBox::SetKeyValue(String key_value)
{
	if (FDataset != NULL)
	{
		Clear();

		TStringList* keys = new TStringList();

		keys->Delimiter		= FKeyValueSeparator;
		keys->DelimitedText = key_value;

		for (int i = 0; i < Items->Count; i++)
		{
			if (ListItems[i]->ClassName() ==  "TDBListBoxItem")
			{
				TDBListBoxItem* lbi = (TDBListBoxItem*)ListItems[i];

				if (Multiselect)
				{
					if (keys->IndexOf(lbi->Key) >= 0)
					{
						TCheckBox* lbi_checkbox = (TCheckBox*)lbi->FindStyleResource("check");

						if (lbi_checkbox)
							lbi_checkbox->IsChecked = true;

						CheckedItemsList->Add(lbi);
					}
				}
				else if (lbi->Key == keys->Strings[0])
				{
					ItemIndex = i;
					break;
				}
			}
		}

		delete keys;

		Repaint();
	}
}
//---------------------------------------------------------------------------
TComboListBox* __fastcall TDBComboBox::CreateListBox(void)
{
	TDBComboListBox* res 	= new TDBComboListBox(this);
	res->OnItemCheckClick	= OnItemCheckClick;
	res->OnItemClick 		= OnItemClick;

	return res;
}
//---------------------------------------------------------------------------

void __fastcall TDBComboBox::OnItemCheckClick(TListBoxItem *item)
{
	if (item)
	{
		if (CheckedItemsList->IndexOf(item) < 0)
			CheckedItemsList->Add(item);
		else
			CheckedItemsList->Remove(item);
	}
}
//---------------------------------------------------------------------------

void __fastcall TDBComboBox::OnItemClick(TListBoxItem *item)
{
	CheckedItemsList->Clear();

	if (Multiselect)
	{
		TCheckBox* cb 	   = (TCheckBox*)item->FindStyleResource("check");

		if (cb != NULL)
			cb->IsChecked  = true;

		CheckedItemsList->Add(item);
	}
}
//---------------------------------------------------------------------------


