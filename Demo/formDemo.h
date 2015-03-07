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

#ifndef formDemoH
#define formDemoH
//---------------------------------------------------------------------------
#include <System.Classes.hpp>
#include <FMX.Controls.hpp>
#include <FMX.Forms.hpp>
#include <FMX.ListBox.hpp>
#include <FMX.Types.hpp>
#include <FMX.StdCtrls.hpp>
#include <FMX.Layouts.hpp>
#include <FMX.Memo.hpp>
#include <FMX.Edit.hpp>
#include <Datasnap.DBClient.hpp>

#include <TDBComboBox.h>
//---------------------------------------------------------------------------
class TfrmDemo : public TForm
{
__published:	// IDE-managed Components
	TButton *btnMultiselect;
	TMemo *mmSelectedItems;
	TButton *btnClear;
	TButton *btnSetKeyValue;
	TButton *btnAlternateRowColor;
	TPanel *pnlComponent;
	TRadioButton *rbUseItems;
	TRadioButton *rbUseDataset;
	TLabel *lblSelectedItems;
	TLabel *lblKeyValue;
	TEdit *edtKeyValue;
	TLabel *lblSeparator;
	TEdit *edtSeparator;
	void __fastcall btnMultiselectClick(TObject *Sender);
	void __fastcall btnClearClick(TObject *Sender);
	void __fastcall btnSetKeyValueClick(TObject *Sender);
	void __fastcall btnAlternateRowColorClick(TObject *Sender);
	void __fastcall rbUseItemsClick(TObject *Sender);
	void __fastcall rbUseDatasetChange(TObject *Sender);
	void __fastcall edtSeparatorTyping(TObject *Sender);

private:	// User declarations
	TDBComboBox* DBComboBox;
	TClientDataSet *Dataset;

	void __fastcall ClearAll(void);
	void __fastcall DBComboBoxCloseUp(TObject *Sender);
	void __fastcall FillItems(void);
	void __fastcall CreateDataSet(void);
public:		// User declarations
	__fastcall TfrmDemo(TComponent* Owner);

};
//---------------------------------------------------------------------------
extern PACKAGE TfrmDemo *frmDemo;
//---------------------------------------------------------------------------
#endif
