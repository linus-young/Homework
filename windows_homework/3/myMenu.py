# -*- coding: cp936 -*-
""" create ChineseMenu and EnglishMenu to Simplify the code """

import wx

def initChineseMenu():
	menuBar = wx.MenuBar()

	fileMenu = wx.Menu()
	fileMenu.Append( wx.ID_EXIT, u"�˳�(&x)", "Exit this application")

	dialogMenu = wx.Menu()
	dialogMenu.Append( 201, u"ģʽ�Ի���(&M)\tCtrl+A", "open mode dialog")
	dialogMenu.Append( 202, u"��ģʽ�Ի���(&L\tCtrl+B", "open modeless dialog")
	dialogMenu.Append( 203, u"�ļ��Ի���(&F)\tCtrl+C", "open file dialog")

	cursorMenu = wx.Menu()
	cursorMenu.Append( 301, u"���&1(��ͷ)\tCtrl+1", "use arrow cursor", wx.ITEM_RADIO )
	cursorMenu.Append( 302, u"���&2(ʮ��)\tCtrl+2", "use cross cursor", wx.ITEM_RADIO )
	cursorMenu.Append( 303, u"���&3(�Զ���)\tCtrl+3", "use user defined cursor", wx.ITEM_RADIO )

	langMenu = wx.Menu()
	langMenu.Append( 401,u"����(&C)\tCtrl+Shift+C", "use Chinese", wx.ITEM_RADIO )
	langMenu.Append( 402,"English(&E)\tCtrl+Shift+E", "use English", wx.ITEM_RADIO )

	aboutMenu = wx.Menu()
	aboutMenu.Append( 501, u"������Ϣ(&I)\tF1", "")

	menuBar.Append( fileMenu, u"�ļ�(&F)")
	menuBar.Append( dialogMenu, u"�Ի���(&D)")
	menuBar.Append( cursorMenu, u"�������(&C)")
	menuBar.Append( langMenu, u"����(&L)")
	menuBar.Append( aboutMenu, u"����(&A)")
	menuBar.Check( 401, True )

	return menuBar


def initEnglishMenu():
	menuBar = wx.MenuBar()

	fileMenu = wx.Menu()
	fileMenu.Append( wx.ID_EXIT, "E&xit", "Exit this application")

	dialogMenu = wx.Menu()
	dialogMenu.Append( 201, "&ModalDialog...\tCtrl+A", "open mode dialog")
	dialogMenu.Append( 202, "Modal&LessDialog...\tCtrl+B", "open modeless dialog")
	dialogMenu.Append( 203, "&File Dialog...\tCtrl+C", "open file dialog")

	cursorMenu = wx.Menu()
	cursorMenu.Append( 301, "Cursor&1(ARROW)\tCtrl+1", "use arrow cursor", wx.ITEM_RADIO )
	cursorMenu.Append( 302, "Cursor&2(CROSS)\tCtrl+2", "use cross cursor", wx.ITEM_RADIO )
	cursorMenu.Append( 303, "Cursor&3(UserDefined)\tCtrl+3", "use user defined cursor", wx.ITEM_RADIO )

	langMenu = wx.Menu()
	langMenu.Append( 401,u"����(&C)\tCtrl+Shift+C", "use Chinese", wx.ITEM_RADIO )
	langMenu.Append( 402,"English(&E)\tCtrl+Shift+E", "use English", wx.ITEM_RADIO )

	aboutMenu = wx.Menu()
	aboutMenu.Append( 501, "Program &Information\tF1", "")

	menuBar.Append( fileMenu, "&File")
	menuBar.Append( dialogMenu, "&Dialog")
	menuBar.Append( cursorMenu, "&Cursor")
	menuBar.Append( langMenu, "&Language")
	menuBar.Append( aboutMenu, "&About")
	menuBar.Check( 402, True )

	return menuBar
