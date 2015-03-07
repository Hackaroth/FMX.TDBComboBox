/*---------------------------------------------------------------------------
 *
 * TDBComboBox Class Application Demo
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

#include <fmx.h>
#pragma hdrstop

#include "formDemo.h"

//---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma resource "*.fmx"
TfrmDemo *frmDemo;
//---------------------------------------------------------------------------
__fastcall TfrmDemo::TfrmDemo(TComponent* Owner)
	: TForm(Owner)
{
	DBComboBox 					= new TDBComboBox(this);
	DBComboBox->OnClosePopup 	= DBComboBoxCloseUp;
	DBComboBox->Parent 			= pnlComponent;

	DBComboBox->Position->X 	= 10;
	DBComboBox->Position->Y 	= 40;

	DBComboBox->Width 			= 220;

	rbUseItems->IsChecked		= true;

	edtSeparator->MaxLength		= 1;
	edtSeparator->Text			= DBComboBox->KeyValueSeparator;

	CreateDataSet();
	FillItems();
}
//---------------------------------------------------------------------------
void __fastcall TfrmDemo::ClearAll(void)
{
	DBComboBox->Clear();
	DBComboBox->Items->Clear();
	mmSelectedItems->Lines->Clear();
	edtKeyValue->Text = "";
}
//---------------------------------------------------------------------------

void __fastcall TfrmDemo::FillItems(void)
{
	DBComboBox->Dataset = NULL;

	ClearAll();

	DBComboBox->Items->Add("Item 1");
	DBComboBox->Items->Add("Item 2");
	DBComboBox->Items->Add("Item 3");
	DBComboBox->Items->Add("Item 4");
	DBComboBox->Items->Add("Item 5");
}
//---------------------------------------------------------------------------

void __fastcall TfrmDemo::btnMultiselectClick(TObject *Sender)
{
	DBComboBox->Multiselect = !DBComboBox->Multiselect;
}
//---------------------------------------------------------------------------
void __fastcall TfrmDemo::DBComboBoxCloseUp(TObject *Sender)
{
	mmSelectedItems->Lines->Clear();

	if (DBComboBox->Multiselect)
	{
		for (int i = 0; i < DBComboBox->CheckedItems->Count; i++)
			mmSelectedItems->Lines->Add(DBComboBox->CheckedItems->Items[i]->Text);

	}
	else if (DBComboBox->Selected)
		mmSelectedItems->Lines->Add(DBComboBox->Selected->Text);

	edtKeyValue->Text = DBComboBox->KeyValue;
}
//---------------------------------------------------------------------------

void __fastcall TfrmDemo::btnClearClick(TObject *Sender)
{
	DBComboBox->Clear();
	mmSelectedItems->Lines->Clear();
	edtKeyValue->Text = "";
}
//---------------------------------------------------------------------------

void __fastcall TfrmDemo::btnSetKeyValueClick(TObject *Sender)
{
	DBComboBox->KeyValue = edtKeyValue->Text;
	DBComboBoxCloseUp(this);
}
//---------------------------------------------------------------------------

void __fastcall TfrmDemo::btnAlternateRowColorClick(TObject *Sender)
{
	DBComboBox->AlternateRowBackground = !DBComboBox->AlternateRowBackground;
}
//---------------------------------------------------------------------------

void __fastcall TfrmDemo::rbUseItemsClick(TObject *Sender)
{
	FillItems();
}
//---------------------------------------------------------------------------
void __fastcall TfrmDemo::CreateDataSet(void)
{
	Dataset = new TClientDataSet(this);
	Dataset->FieldDefs->Add("Id",ftBCD);
	Dataset->FieldDefs->Add("Name",ftString,20);
	Dataset->CreateDataSet();

	Dataset->Open();
	Dataset->Append();
	Dataset->FieldByName("Id")->AsInteger = 1;
	Dataset->FieldByName("Name")->AsString = "DB Item 1";
	Dataset->Post();

	Dataset->Append();
	Dataset->FieldByName("Id")->AsInteger = 2;
	Dataset->FieldByName("Name")->AsString = "DB Item 2";
	Dataset->Post();

	Dataset->Append();
	Dataset->FieldByName("Id")->AsInteger = 3;
	Dataset->FieldByName("Name")->AsString = "DB Item 3";
	Dataset->Post();


	Dataset->Append();
	Dataset->FieldByName("Id")->AsInteger = 4;
	Dataset->FieldByName("Name")->AsString = "DB Item 4";
	Dataset->Post();


	Dataset->Append();
	Dataset->FieldByName("Id")->AsInteger = 5;
	Dataset->FieldByName("Name")->AsString = "DB Item 5";
	Dataset->Post();
}
//---------------------------------------------------------------------------

void __fastcall TfrmDemo::rbUseDatasetChange(TObject *Sender)
{
	ClearAll();

	DBComboBox->DisplayFieldName = "Name";
	DBComboBox->ValueFieldName   = "Id";

	DBComboBox->Dataset = Dataset;
}
//---------------------------------------------------------------------------

void __fastcall TfrmDemo::edtSeparatorTyping(TObject *Sender)
{
	if (!edtSeparator->Text.IsEmpty())
		DBComboBox->KeyValueSeparator = edtSeparator->Text[1];
}
//---------------------------------------------------------------------------

