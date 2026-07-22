/***************************************************************************/
/*                        ExtensionesFicheros.h                            */
/*-------------------------------------------------------------------------*/
/* Librería: Sistema                                                       */
/* Versión:  1.1.0                                                         */
/* Fecha:    26/10/2006                                                    */
/* Autor:    Ginés Jiménez Sánchez                                         */
/*-------------------------------------------------------------------------*/
/* Descripción:                                                            */
/* Fichero de cabecera que contiene la definición de las extensiones de    */
/* fichero asociadas a los diferentes tipos de archivo existente, o al     */
/* menos, a los más comunes.                                               */
/*-------------------------------------------------------------------------*/
/* NOTA DEL AUTOR:                                                         */
/* Este módulo está extraído de una librería más completa creada por el    */
/* mismo autor. Por favor, el autor ruega que se le informe de cualquier   */
/* error detectado, así como cualquier añadido o modificación realizado.   */
/* Pueden reportar de los mismos enviando un correo electrónico a la       */
/* dirección: gines_jimenez@safe-mail.net. Gracias.                        */
/***************************************************************************/

#ifndef _ORG_GJS_C_CC_EXTENSIONES_FICHEROS_H
#define _ORG_GJS_C_CC_EXTENSIONES_FICHEROS_H


#define EXT_FIC_TEXTO						"txt"
#define EXT_FIC_BINARIO						"bin" 

#define EXT_FIC_FUENTE_TRUE_TYPE			"ttf"
#define EXT_FIC_FUENTE_BITMAP				"fon"

#define EXT_FIC_GRAFICO_BITMAP				"bmp"		// Bitmap graphics (PC Paintbrush - many)
#define EXT_FIC_GRAFICO_BITMAP_2			"bm"		// Bitmap graphics
		
#define EXT_FIC_CABECERA_C					"h" 
#define EXT_FIC_CODIGO_C					"c"			// C source code file
#define EXT_FIC_CODIGO_C_2					"c++"		// C++ source code file
#define EXT_FIC_CODIGO_C_3					"cpp"		// C++ source code file
#define EXT_FIC_CODIGO_C_4					"cxx"		// Cxx source code file

#define EXT_FIC_VISUAL_BASIC				"vb"		
#define EXT_FIC_CSHARP						"cs"		

#define EXT_FIC_INTERFAZ					"idl"		// Interface Definition file

#define EXT_FIC_XML							"xml"		// Extensible Markup Language file
#define EXT_FIC_HTML						"htm"		// HyperText Markup Language document
#define EXT_FIC_HTML_2						"html"		// HyperText Markup Language document

#define EXT_FIC_DBASE						"dbf"		// Database file (dBASE III/IV - FoxPro - dBFast - DataBoss)
#define EXT_FIC_SHAPE						"shp"		// Shape file and source file for text fonts (AutoCAD)
#define EXT_FIC_LOCALIZACION_SHAPE			"shx"		// Shape entities (AutoCAD)
#define EXT_FIC_INDICE_SHAPE				"qix" 
#define EXT_FIC_RASTER_SUN					"ras"		// Sun Rasterfile graphics
#define EXT_FIC_GEORREF_RASTER_SUN			"rsw"		// Formato específico creado en Telefónica I+D 

#define EXT_FIC_GZIP			            "gz"		//  Compressed file archive created by GZIP (GNU zip)

#define EXT_FIC_ERROR						"err"

#define EXT_FIC_ARCVIEW						"avx"		// ArcView file

#define EXT_FIC_COPIA_SEG					"bak"		// Backup file

#define EXT_FIC_LOG							"log"		// Log file

#define EXT_FIC_INFO_TABLA					"tab"		// Fichero de información de tabla de datos.

#define EXT_FIC_INFO_SHAPE					"shi"		// Fichero de información de un shape.

#define EXT_FIC_GENERADOR_ID				"gid"


/*
#define EXT_FIC_           "#24" // Printer data file for 24 pin matrix printer (LocoScript)
#define EXT_FIC_           "#ib" // Printer data file (LocoScript)
#define EXT_FIC_           "#sc" // Printer data file (LocoScript)
#define EXT_FIC_           "#st" // Standard mode printer definitions (LocoScript)
#define EXT_FIC_           "$#!" // Cryptext
#define EXT_FIC_           "$$$" // Temporary file
#define EXT_FIC_           "000" // Compressed harddisk data (DoubleSpace)
#define EXT_FIC_           "001" // Fax (many)
#define EXT_FIC_           "075" // 75x75 dpi display font (Ventura Publisher)
#define EXT_FIC_           "085" // 85x85 dpi display font (Ventura Publisher)
#define EXT_FIC_           "091" // 91x91 dpi display font (Ventura Publisher)
#define EXT_FIC_           "096" // 96x96 dpi display font (Ventura Publisher)
#define EXT_FIC_           "0b" // Printer font with lineDraw extended character set (PageMaker)
#define EXT_FIC_           "1" // Roff/nroff/troff/groff source for manual page (cawf2.zip)
#define EXT_FIC_           "113" // Iomega Backup file
#define EXT_FIC_           "123" // Lotus file
#define EXT_FIC_           "15u" // Printer font with PI font set (PageMaker)
#define EXT_FIC_           "1st" // Usually README.1ST text
#define EXT_FIC_           "2d" // 2d Drawings (VersaCad)
#define EXT_FIC_           "2dl" // 2d Libraries (VersaCad)
#define EXT_FIC_           "3d" // 3d Drawings (VersaCad)
#define EXT_FIC_           "3dl" // 3d Libraries (VersaCad)
#define EXT_FIC_           "301" // Fax (Super FAX 2000 - Fax-Mail 96))
#define EXT_FIC_           "386" // Intel 80386 processor driver (Windows 3.x)
#define EXT_FIC_           "3ds" // Graphics (3D Studio)
#define EXT_FIC_           "3fx" // Effect (CorelChart)
#define EXT_FIC_           "3gp" // Multimedia File
#define EXT_FIC_           "3gr" // Data file (Windows Video Grabber)
#define EXT_FIC_           "3ko" // NGRAIN Mobilizer
#define EXT_FIC_           "3t4" // Binary file converter to ASCII (Util3)
#define EXT_FIC_           "411" // Sony Mavica Data file
#define EXT_FIC_           "4c$" // Datafile (4Cast/2)
#define EXT_FIC_           "4sw" // 4dos Swap File
#define EXT_FIC_           "4th" // Forth source code file (ForthCMP - LMI Forth)
#define EXT_FIC_           "5cr" // Preconfigured drivers for System 5cr and System 5cr Plus 
#define EXT_FIC_           "669" // Music (8 channels) (The 669 Composer)
#define EXT_FIC_           "6cm" // Music (6 Channel Module) (Triton FastTracker)
#define EXT_FIC_           "8" // A86 assembler source code file
#define EXT_FIC_           "8cm" // Music (8 Channel Module) (Triton FastTracker)
#define EXT_FIC_           "8m" // Printer font with Math 8 extended character set (PageMaker)
#define EXT_FIC_           "8u" // Printer font with Roman 8 extended character set (PageMaker)
#define EXT_FIC_           "a" // Ada source code file

#define EXT_FIC_           "a11" // Graphics AIIM image file
#define EXT_FIC_           "a2b" // A2B Player Playlist 
#define EXT_FIC_           "a3d" // Amapi 3D Modeling file
#define EXT_FIC_           "a3m" // Unpackaged Authorware MacIntosh file
#define EXT_FIC_           "a3w" // Unpackaged Authorware Windows file
#define EXT_FIC_           "a4a" // Authorware 4.x Library 
#define EXT_FIC_           "a4m" // Unpackaged Authorware MacIntosh file
#define EXT_FIC_           "a4p" // Authorware file packaged without runtime
#define EXT_FIC_           "a4w" // Unpackaged Authorware Windows file
#define EXT_FIC_           "a5w" // Unpackaged Authorware Windows file
#define EXT_FIC_           "aab" // Macromedia Authorware Binary
#define EXT_FIC_           "aam" // Authorware shocked file
#define EXT_FIC_           "ab2" // Parson's Address Book
#define EXT_FIC_           "ab6" // Datafile (ABStat)
#define EXT_FIC_           "ab8" // Datafile (ABStat)
#define EXT_FIC_           "aba" // Palm Address Book file
#define EXT_FIC_           "abc" // ABC FLOWCHARTER 1.x flowchart

#define EXT_FIC_           "abd" // AmBiz Bonus Calculator data file

#define EXT_FIC_           "abf" // Adobe Binary Font
#define EXT_FIC_           "abk" // Automatic backup file (CorelDRAW)
#define EXT_FIC_           "abm" // ImagePals Photo Album Document


#define EXT_FIC_           "abs" // Abstracts (info file)


#define EXT_FIC_           "abw" // AbiWord document
#define EXT_FIC_           "abx" // WordPerfect Address Book file
#define EXT_FIC_           "ac3" // AC3 Audio File Format 
#define EXT_FIC_           "aca" // Microsoft Agent Character file

#define EXT_FIC_           "acb" // Graphics (ACMB)
#define EXT_FIC_           "acc" // Program (DR-DOS - ViewMax) (GEM / resident)
#define EXT_FIC_           "acd" // Sonic Foundry Acid music file
#define EXT_FIC_           "ace" // Ace Archiver compressed file
#define EXT_FIC_           "acf" // Microsoft Agent Character file

#define EXT_FIC_           "aci" // ACI Development Appraisal
#define EXT_FIC_           "acl" // Document file (Audit Command Language)
#define EXT_FIC_           "acm" // Audio Compression Manager Driver



#define EXT_FIC_           "" // Interplay compressed Sound file 
#define EXT_FIC_           "acs" // MS Agent Character file
#define EXT_FIC_           "act" // Actor source code file


#define EXT_FIC_           "acv" // OS/2 Audio Drivers

#define EXT_FIC_           "ad" // Screen saver data (AfterDark)
#define EXT_FIC_           "ada" // Ada source code file
#define EXT_FIC_           "adb" // Ada Package Body
#define EXT_FIC_           "adc" // Bitmap graphics (16 colors) (Scanstudio)
#define EXT_FIC_           "adf" // Adapter Description file



#define EXT_FIC_           "adi" // Graphics (AutoCAD)
#define EXT_FIC_           "adl" // Mca adapter description library (QEMM)
#define EXT_FIC_           "adm" // After Dark Screen Saver Module   



#define EXT_FIC_           "adn" // Add-in (Lotus 1-2-3)
#define EXT_FIC_           "ado" // Photoshop Duotone Options

#define EXT_FIC_           "adp" // FaxWorks Modem setup file



#define EXT_FIC_           "adr" // Address Book

#define EXT_FIC_           "ads" // Ada Package Specification
#define EXT_FIC_           "adt" // Datafile for cardfile application (HP NewWave)

#define EXT_FIC_           "adx" // Document (Archetype Designer)
#define EXT_FIC_           "adz" // GZ-Packed Amiga Disk file
#define EXT_FIC_           "aeh" // iPer Advanced Embedded Hypertext
#define EXT_FIC_           "aex" // PGP Armored Extracted Public Encryption Key
#define EXT_FIC_           "af2" // Flowchart (ABC FlowCharter 2.0)
#define EXT_FIC_           "aff" // AnyForm Form file
#define EXT_FIC_           "afi" // Truevision bitmap graphics
#define EXT_FIC_           "afl" // Font file (for Allways) (Lotus 1-2-3)
#define EXT_FIC_           "afm" // Type 1 font metric ASCII data for font installer (ATM - many)

#define EXT_FIC_           "aft" // AnyForm template file
#define EXT_FIC_           "agp" // Aspen Graphics Pages
#define EXT_FIC_           "agw" // Aspen Graphics Windows
#define EXT_FIC_           "ai" // Vector graphics (Adobe Illustrator)
#define EXT_FIC_           "aiff" // Audio interchange file format
#define EXT_FIC_           "ain" // Compressed file archive created by AIN
#define EXT_FIC_           "aio" // APL file transfer format file
#define EXT_FIC_           "air" // Automatic Image 
#define EXT_FIC_           "egistration .ais" // Array of Intensity Samples graphics (Xerox)
#define EXT_FIC_           "aix" // Datafile for cardfile application (HP NewWave)
#define EXT_FIC_           "alb" // JASC Image Commander Album


#define EXT_FIC_           "albm" // webAlbum Photo Album

#define EXT_FIC_           "all" // Format file for working pages (Always)


#define EXT_FIC_           "als" // Alias Image

#define EXT_FIC_           "alt" // Menu file (WordPerfect Library)
#define EXT_FIC_           "alz" // ALZip Compressed file
#define EXT_FIC_           "amf" // Music (Advanced Module Format)
#define EXT_FIC_           "amg" // Compressed file archive created by AMGC

#define EXT_FIC_           "amp" // Photoshop Arbitrary Map Settings
#define EXT_FIC_           "anc" // Animation file format (MorphInk)
#define EXT_FIC_           "ani" // Animation (Presidio - many)
#define EXT_FIC_           "anm" // Animation (Deluxe Paint Animator)
#define EXT_FIC_           "ann" // Help Annotations (Windows 3.x)
#define EXT_FIC_           "ans" // Ansi graphics (character animation)

#define EXT_FIC_           "aos" // Add-On Software (Nokia 9000)
#define EXT_FIC_           "ap" // Compressed Amiga file archive created by WHAP

#define EXT_FIC_           "apc" // Printer driver (Lotus 1-2-3)
#define EXT_FIC_           "apd" // Printer driver (Lotus 1-2-3)
#define EXT_FIC_           "ape" // Music format (different players)
#define EXT_FIC_           "apf" // Printer driver (Lotus 1-2-3)
#define EXT_FIC_           "api" // Passed parameter file (1st Reader)

#define EXT_FIC_           "apl" // APL work space format file
#define EXT_FIC_           "apm" // ArcPad 6 file
#define EXT_FIC_           "app" // Add-in application file (Symphony)



#define EXT_FIC_           "apr" // Employee performance review (Employee Appraiser)
#define EXT_FIC_           "aps" // MS Visual C++ file

#define EXT_FIC_           "apx" // Appexpert database file (Borland C++ 4.5)
#define EXT_FIC_           "arc" // Compressed file archive created by ARC (arc602.exe/pk361.exe)

#define EXT_FIC_           "arf" // Automatic Response file
#define EXT_FIC_           "arg" // AutoCAD Profile Export file
#define EXT_FIC_           "ari" // Compressed file archive created by ARI
#define EXT_FIC_           "arj" // Compressed file archive created by ARJ (arj241.exe)
#define EXT_FIC_           "arl" // AOL Organizer File
#define EXT_FIC_           "ark" // Arc file archive created by CP/M port of ARC file archiver

#define EXT_FIC_           "arr" // Arrangement (Atari Cubase)
#define EXT_FIC_           "ars " // Adobe After Effects Render
#define EXT_FIC_           "art" // Graphics (scrapbook) (Art Import)

#define EXT_FIC_           "arv" // Arsiv File

#define EXT_FIC_           "arx" // Compressed file archive created by ARX
#define EXT_FIC_           "asa" // MS Visual InterDev file

#define EXT_FIC_           "asc" // Ascii text file

#define EXT_FIC_           "ascx" // Microsoft ASP.NET user control file
#define EXT_FIC_           "asd" // Autosave file (Word for Windows)


#define EXT_FIC_           "asf" // Datafile (STATGRAPHICS)

#define EXT_FIC_           "ash" // Assembly language header file (TASM 3.0)
#define EXT_FIC_           "asi" // Assembler include file (Turbo C - Borland C++)
#define EXT_FIC_           "asl " // Adobe Photoshop Layer file
#define EXT_FIC_           "asm" // Assembly source code file

#define EXT_FIC_           "asmx" // Microsoft .NET Web Service file
#define EXT_FIC_           "aso" // Assembler object (object orientated) file (Turbo Assembler)
#define EXT_FIC_           "asp" // Microsoft Active Server Page


#define EXT_FIC_           "aspx" // Microsoft ASP.NET file
#define EXT_FIC_           "asr" // Ms Automap Route

#define EXT_FIC_           "asx" // Microsoft Windows Media Active Stream Redirector file


#define EXT_FIC_           "at2" // Auto template (Aldus Persuasion 2.0)
#define EXT_FIC_           "atm" // Adobe Type Manager data/info
#define EXT_FIC_           "atn" // Adobe Photoshop Action file
#define EXT_FIC_           "atr" // Lightscape Material Library
#define EXT_FIC_           "att" // AT&T Group 4 Bitmap
#define EXT_FIC_           "au" // Sound (audio) file (SUN Microsystems)
#define EXT_FIC_           "aud" // Audio file
#define EXT_FIC_           "aut" // AutoIt Script

#define EXT_FIC_           "aux" // Auxillary references (TeX/LaTeX)

#define EXT_FIC_           "ava" // Publication (Avagio)
#define EXT_FIC_           "avb" // Inoculan Anti-Virus virus infected file

#define EXT_FIC_           "avd" // Avery Label Pro Data file
#define EXT_FIC_           "avi" // Audio Video Interleaved animation file (Video for Windows)
#define EXT_FIC_           "avs" // Animation file



#define EXT_FIC_           "aw" // Text file (HP AdvanceWrite)
#define EXT_FIC_           "awb" // Lavasoft Ad-aware backup file
#define EXT_FIC_           "awd" // AWD MS Fax


#define EXT_FIC_           "awe" // Adobe Acrobat Bookmark XML file
#define EXT_FIC_           "awk" // Awk script/program
#define EXT_FIC_           "awm" // Movie (Animation Works)
#define EXT_FIC_           "awr" // Telsis Digital Audio file
#define EXT_FIC_           "aws" // Data (STATGRAPHICS)
#define EXT_FIC_           "ax" // DirectShow Filter
#define EXT_FIC_           "axd" // Avery Label Pro Re-Index file

#define EXT_FIC_           "axe" // Paradigm C++ Integrated Debugger file

#define EXT_FIC_           "" // MS Autoroute export file
#define EXT_FIC_           "axg" // MS Autoroute Trip file
#define EXT_FIC_           "axl" // ArcIMS XML Project file
#define EXT_FIC_           "axs" // AMX Axcess control system file format
#define EXT_FIC_           "axt" // ZenWorks snAPPshot ASCII Application Object template

#define EXT_FIC_           "azz" // AZZ Cardfile
#define EXT_FIC_           "b" // Batch list (APPLAUSE)
#define EXT_FIC_           "b&w" // Black and white graphics (atari - mac)
#define EXT_FIC_           "b~k" // backup file

#define EXT_FIC_           "b16" // PCO Graphic file
#define EXT_FIC_           "b1n" // Both mono and color binary screen image (1st Reader)
#define EXT_FIC_           "b1s" // Booksmith
#define EXT_FIC_           "b30" // Printer font (JLaser - Cordata) (Ventura Publisher)
#define EXT_FIC_           "b3d" // 3D Builder file
#define EXT_FIC_           "b8" // Raw graphics (one byte per pixel) plane two (PicLab)
#define EXT_FIC_           "b_w" // Black and white graphics (atari - mac)
#define EXT_FIC_           "bad" // Bad file (Oracle)
#define EXT_FIC_           "bag" // PMMail Mail Index file


#define EXT_FIC_           "bal" // Music score (Ballade)
#define EXT_FIC_           "ban" // Sierra Print Artist Banner 
#define EXT_FIC_           "bar" // Horizontal bar menu object file (dBASE Application Generator)
#define EXT_FIC_           "bas" // Basic source code file
#define EXT_FIC_           "bat" // Batch file (DOS)
#define EXT_FIC_           "bb" // Database backup (Papyrus)
#define EXT_FIC_           "bbl" // Bibliographic reference (TeX/BibTeX)
#define EXT_FIC_           "bbm" // Brush (Deluxe Paint)
#define EXT_FIC_           "bbs" // Bulletin Board System announce or text info file
#define EXT_FIC_           "bcf" // ConfigSafe Snapshot index

#define EXT_FIC_           "bch" // Batch process object file (dBASE Application Generator)

#define EXT_FIC_           "bck" // Backup
#define EXT_FIC_           "bcm" // MS Works Communications file
#define EXT_FIC_           "bcn" // Business Card Pro Design.bcoOutline font description (Bitstream)
#define EXT_FIC_           "bcp" // Borland C++ makefile
#define EXT_FIC_           "bct" // Business Card Designer template 
#define EXT_FIC_           "bcw" // Environment settings (Borland C++ 4.5)
#define EXT_FIC_           "bde" // Borland Database Engine
#define EXT_FIC_           "bdf" // Bitmap Distribution Format font file (X11)

#define EXT_FIC_           "bdr" // Border (MS Publisher)
#define EXT_FIC_           "bez" // Outline font description (Bitstream)
#define EXT_FIC_           "bf2" // Bradford 2 font
#define EXT_FIC_           "bfm" // Font metrics (unix/Frame)
#define EXT_FIC_           "bfx" // Fax (BitFax)
#define EXT_FIC_           "bga" // Bitmap graphics
#define EXT_FIC_           "bgt" // Quicken 2002 Internet Common File .bgiBorland Graphics Interface device driver
#define EXT_FIC_           "bgl" // Flight Simulator scenery file
#define EXT_FIC_           "bgt" // Quicken 2002 Internet Common File 
#define EXT_FIC_           "bib" // Bibliography (ASCII)


#define EXT_FIC_           "bic" // Civilization III Scenario
#define EXT_FIC_           "bid" // BidMaker 2002 file
#define EXT_FIC_           "bif" // Binary Image Format b&w graphics (Image Capture board)
#define EXT_FIC_           "bik" // BioCharter Profile backup file

#define EXT_FIC_           "bio" // OS/2 BIOS
#define EXT_FIC_           "bit" // Bitmap Image  


#define EXT_FIC_           "bk" //  Faxbook (JetFax)
#define EXT_FIC_           "bk!" // Document backup (WordPerfect for Win)
#define EXT_FIC_           "bk1" // Timed backup file for document window 1 (WordPerfect for Win)
#define EXT_FIC_           "bk2" // Timed backup file for document window 2 (WordPerfect for Win)
#define EXT_FIC_           "bk3" // Timed backup file for document window 3 (WordPerfect for Win)
#define EXT_FIC_           "bk4" // Timed backup file for document window 4 (WordPerfect for Win)
#define EXT_FIC_           "bk5" // Timed backup file for document window 5 (WordPerfect for Win)
#define EXT_FIC_           "bk6" // Timed backup file for document window 6 (WordPerfect for Win)
#define EXT_FIC_           "bk7" // Timed backup file for document window 7 (WordPerfect for Win)
#define EXT_FIC_           "bk8" // Timed backup file for document window 8 (WordPerfect for Win)
#define EXT_FIC_           "bk9" // Timed backup file for document window 9 (WordPerfect for Win)
#define EXT_FIC_           "bkf" // Microsoft Backup file
#define EXT_FIC_           "bkg" // Background file

#define EXT_FIC_           "bkp" // Backup file (Write - TurboVidion DialogDesigner)
#define EXT_FIC_           "bkw" // Mirror image of font set (FontEdit)
#define EXT_FIC_           "blb" // DreamWorks Resource Archive
#define EXT_FIC_           "bld" // Bloadable picture (BASIC)
#define EXT_FIC_           "blend" // Blender 3D file
#define EXT_FIC_           "blk" // Temporary file (WordPerfect for Win)



#define EXT_FIC_           "blt" // Saved AIM Buddy List file

#define EXT_FIC_           "bmf" // Corel Image file
#define EXT_FIC_           "bmi" // 3ds max Executable.bmkHelp Bookmarks (Windows 3.x)
#define EXT_FIC_           "bmx" // Buzz music file
#define EXT_FIC_           "bnd" // Typequick file
#define EXT_FIC_           "bnk" // Adlib instrument bank file
#define EXT_FIC_           "bob" // BobDown Downloading Program

#define EXT_FIC_           "bom" // MicroSim PCBoard Bill of Materials


#define EXT_FIC_           "boo" // Compressed file ASCII archive created by BOO (msbooasm.arc)
#define EXT_FIC_           "book" // Adobe FrameMaker Book
#define EXT_FIC_           "box" // Myriad Jukebox file

#define EXT_FIC_           "bpc" // Chart (Business Plan Toolkit)
#define EXT_FIC_           "bpl" // Delphi Library
#define EXT_FIC_           "bpt" // Bitmap fills file (CorelDRAW)
#define EXT_FIC_           "bqy" // BrioQuery file
#define EXT_FIC_           "br" // Script (Bridge)
#define EXT_FIC_           "brd" // Eagle Layout file
#define EXT_FIC_           "brf" // Braille ASCII file 
#define EXT_FIC_           "brk" // Fax (Brooktrout Fax-Mail)
#define EXT_FIC_           "bro" // Tree Professional Broadleaf Creator file
#define EXT_FIC_           "brp" // Tree Professional Broadleaf Creator image
#define EXT_FIC_           "brt" // Micrografx Picture Publisher file
#define EXT_FIC_           "brx" // Multimedia browsing index
#define EXT_FIC_           "bsa" // Compressed file archive created by BSARC
#define EXT_FIC_           "bsb" // MapInfo Sea Chart

#define EXT_FIC_           "bsc" // Compressed Apple II file archive created by BINSCII


#define EXT_FIC_           "bsl" // BSPlayer Configuration file
#define EXT_FIC_           "bsp" // Half-life/TFC/CS Map

#define EXT_FIC_           "bst" // BibTeX Style file
#define EXT_FIC_           "btm" // Batch To Memory batch file (4DOS)
#define EXT_FIC_           "bto" // Baytex Organix! 2001 Language Kit
#define EXT_FIC_           "btr" // Btrieve Database file

#define EXT_FIC_           "btx " // DB/TextWorks Database Term & Indexes 
#define EXT_FIC_           "bud" // Quicken Backup
#define EXT_FIC_           "bug" // Bugs and Problems
#define EXT_FIC_           "bup" // Backup file
#define EXT_FIC_           "but" // Button definitions (Buttons!)
#define EXT_FIC_           "buy" // Datafile format (movie)
#define EXT_FIC_           "bv1" // Overflow file below insert point in Doc 1 (WordPerfect for Win)
#define EXT_FIC_           "bv2" // Overflow file below insert point in Doc 2 (WordPerfect for Win)
#define EXT_FIC_           "bv3" // Overflow file below insert point in Doc 3 (WordPerfect for Win)
#define EXT_FIC_           "bv4" // Overflow file below insert point in Doc 4 (WordPerfect for Win)
#define EXT_FIC_           "bv5" // Overflow file below insert point in Doc 5 (WordPerfect for Win)
#define EXT_FIC_           "bv6" // Overflow file below insert point in Doc 6 (WordPerfect for Win)
#define EXT_FIC_           "bv7" // Overflow file below insert point in Doc 7 (WordPerfect for Win)
#define EXT_FIC_           "bv8" // Overflow file below insert point in Doc 8 (WordPerfect for Win)
#define EXT_FIC_           "bv9" // Overflow file below insert point in Doc 9 (WordPerfect for Win)
#define EXT_FIC_           "bwb" // Spreadsheet application (Visual Baler)
#define EXT_FIC_           "bwi" // Blindread/Blindwrite
#define EXT_FIC_           "bwr" // Beware (buglist) (Kermit)
#define EXT_FIC_           "bwt" // Blindread/Blindwrite
#define EXT_FIC_           "bxx" // blaxxun Contact
#define EXT_FIC_           "bz2" // Bzip 2 UNIX Compressed file 
#define EXT_FIC_           "c--" // Source code (Sphinx C--)
#define EXT_FIC_           "c00" // Print file (Ventura Publisher)
#define EXT_FIC_           "c01" // Genesis 2000 
#define EXT_FIC_           "c2d" // WinOnCD CD Image .c60Midtronics Battery Management Software
#define EXT_FIC_           "c86" // C source code file (Computer Innovation C86)
#define EXT_FIC_           "ca" //  Initial cache data for root domain servers (Telnet)
#define EXT_FIC_           "cab" // Cabinet File (Microsoft installation archive)
#define EXT_FIC_           "cad" // Softdesk Drafix CAD File
#define EXT_FIC_           "cac" // dBASE IV executable when caching on/off (see cachedb.bat)
#define EXT_FIC_           "cad" // Document (Drafix Windows CAD)
#define EXT_FIC_           "cag" // MS Clip Gallery Catalog file
#define EXT_FIC_           "cal" // Calendar file (Windows 3.x)


#define EXT_FIC_           "calb" // Coolect Album file (Coolect Album Player; www.coolect.com)
#define EXT_FIC_           "cam" // Casio Camera Graphic
#define EXT_FIC_           "can" // Fax (Navigator Fax)
#define EXT_FIC_           "cap" // Caption (Ventura Publisher)

#define EXT_FIC_           "car" // AtHome Assistant file


#define EXT_FIC_           "cas" // Comma-delimited ASCII File
#define EXT_FIC_           "cat" // Catalog (dBASE IV)
#define EXT_FIC_           "cb" // Clean Boot File (Microsoft)Brief Macro Source Code 
#define EXT_FIC_           "cbc" // Fuzzy logic system (CubiCalc)
#define EXT_FIC_           "cbf" // Calendar Builder file
#define EXT_FIC_           "cbl" // Cobol source code file
#define EXT_FIC_           "cbm" // Compiled bitmap graphics (XLib)
#define EXT_FIC_           "cbp" // CentralBuilder Project
#define EXT_FIC_           "cbt" // Computer Based Training (many)
#define EXT_FIC_           "cc" //  C++ source code file
#define EXT_FIC_           "cca" // CC:Mail archive file
#define EXT_FIC_           "ccb" // Visual Basic Animated Button Configuration
#define EXT_FIC_           "ccc" // Bitmap graphics (native format) (Curtain Call)
#define EXT_FIC_           "ccd" // CloneCd Related file

#define EXT_FIC_           "cce" // Calendar Creator 2 Event file
#define EXT_FIC_           "ccf" // Communications configuration file (Symphony)
#define EXT_FIC_           "cch" // Chart (CorelChart)
#define EXT_FIC_           "ccl" // Communication Command Language file (Intalk)
#define EXT_FIC_           "cco" // Btx Graphics file (XBTX)
#define EXT_FIC_           "cct" // Macromedia Director Shockwave file
#define EXT_FIC_           "ccx" // Corel PrintHouse file
#define EXT_FIC_           "cda" // CD Audio Track
#define EXT_FIC_           "cdb" // Card database (CardScan)

#define EXT_FIC_           "cde" // Honeywell Hybrid Control Designer
#define EXT_FIC_           "cdf" // Graphics (netcdf)
#define EXT_FIC_           "cdi" // Phillips Compact Disk Interactive format
#define EXT_FIC_           "cdk" // Document (Atari Calamus)
#define EXT_FIC_           "cdl" // CaseWare Working Papers Document Link

#define EXT_FIC_           "cdm" // Visual dBASE Custom Data Module
#define EXT_FIC_           "cdp" // CD/Spectrum Pro
#define EXT_FIC_           "cdr" // Vector graphics (CorelDRAW native format)
#define EXT_FIC_           "cdt" // Data (CorelDraw 4.0)
#define EXT_FIC_           "cdx" // Compound index (FoxPro)
#define EXT_FIC_           "ce" //  Main.ce (The FarSide Computer Calendar)
#define EXT_FIC_           "ceg" // Bitmap graphics (Tempra Show - Edsun Continuous Edge Graphics)
#define EXT_FIC_           "cel" // Graphics (Autodesk Animator - Lumena)
#define EXT_FIC_           "cf" //  Configuration file (imake)
#define EXT_FIC_           "cfb" // Comptons multimedia file
#define EXT_FIC_           "cfc" // Macromedia Coldfusion component extension
#define EXT_FIC_           "cfg" // Configuration
#define EXT_FIC_           "cfl" // Chart (CorelFLOW)
#define EXT_FIC_           "cfm" // ColdFusion Markup Language (Allaire)
#define EXT_FIC_           "cfn" // Font data (Atari Calamus)
#define EXT_FIC_           "cfo" // C Form Object internal format object file (TCU Turbo C Utilities)
#define EXT_FIC_           "cfp" // Fax (The Complete Fax Portable)
#define EXT_FIC_           "cga" // CGA display font (Ventura Publisher)
#define EXT_FIC_           "cgi" // Common Gateway Interface script
#define EXT_FIC_           "cgm" // Computer Graphics Metafile vector graphics (A&L - HG - many)
#define EXT_FIC_           "ch" //  Header file (Clipper 5)
#define EXT_FIC_           "ch3" // Chart (Harvard Graphics 3.0)
#define EXT_FIC_           "ch4" // Presentation (Charisma 4.0)
#define EXT_FIC_           "chd" // Font descriptor (FontChameleon)
#define EXT_FIC_           "chi" // Document (ChiWriter)
#define EXT_FIC_           "chk" // Recovered data (ChkDsk)

#define EXT_FIC_           "chl" // Configuration History Log
#define EXT_FIC_           "chm" // Compiled HTML
#define EXT_FIC_           "chn" // Data (Ethnograph 3)
#define EXT_FIC_           "cho" // ChordPro file
#define EXT_FIC_           "chp" // Chapter file (Ventura Publisher)
#define EXT_FIC_           "chr" // Character set (Turbo C - Turbo Pascal)
#define EXT_FIC_           "cht" // Chart (Harvard Graphics 2.0 - SoftCraft Presenter)

#define EXT_FIC_           "cid" // AnalogX Caller ID file
#define EXT_FIC_           "cif" // Caltech Intermediate Format graphics

#define EXT_FIC_           "cil" // Clip Gallery Download Package
#define EXT_FIC_           "cix" // Database index (TCU Turbo C Utilities)
#define EXT_FIC_           "ckb" // Keyboard mapping (Borland C++ 4.5)
#define EXT_FIC_           "cl" //  Common LISP source code file
#define EXT_FIC_           "cl3" // Easy CD Creator Layout file
#define EXT_FIC_           "cl4" // Easy CD Creator Layout file
#define EXT_FIC_           "cl5" // Easy CD Creator Layout file
#define EXT_FIC_           "clb" // ICQ Contact List


#define EXT_FIC_           "clp" // Clip art graphics (Quattro Pro)


#define EXT_FIC_           "clr" // Color binary screen image (1st Reader)

#define EXT_FIC_           "cls" // C++ class definition file
#define EXT_FIC_           "cm" //  Data file (CraftMan)
#define EXT_FIC_           "cmd" // Batch file (OS/2)


#define EXT_FIC_           "cmf" // FM-music file (Creative Music File)
#define EXT_FIC_           "cmk" // Card (Card Shop Plus)
#define EXT_FIC_           "cmm" // Cmm script (batch) file (CEnvi)
#define EXT_FIC_           "cmo" // Virtools Composition file
#define EXT_FIC_           "cmp" // Header file for PostScript printer files (CorelDRAW)


#define EXT_FIC_           "cmq" // Culturemetrics file
#define EXT_FIC_           "cmt" // Culturemetrics file
#define EXT_FIC_           "cmv" // Animation (CorelMove CorelDraw 4.0)
#define EXT_FIC_           "cmx" // Corel PhotoPaint Image



#define EXT_FIC_           "cnc" // CNC general program data
#define EXT_FIC_           "cnd" // ControlDraw file

#define EXT_FIC_           "cnf" // Configuration (program - printer setup)
#define EXT_FIC_           "cnt" // Helpfile contents
#define EXT_FIC_           "cnv" // Data conversion support file (Word for Windows)

#define EXT_FIC_           "cob" // Cobol source code file
#define EXT_FIC_           "cod" // Datafile (Forecast Plus - MS Multiplan - StatPac Gold)



#define EXT_FIC_           "col" // Color palette (Autodesk Animator - many)

#define EXT_FIC_           "com" // Command (memory image of executable program) (DOS)
#define EXT_FIC_           "con" // Configuration file (Simdir)
#define EXT_FIC_           "cor" // Protein Structure file


#define EXT_FIC_           "cpd" // Script (Complaints Desk)
#define EXT_FIC_           "cpe" // MS Fax Cover Sheet
#define EXT_FIC_           "cpf" // Fax (The Complete Fax)
#define EXT_FIC_           "cph" // Corel Print House image
#define EXT_FIC_           "cpi" // Code Page Information file (DOS)

#define EXT_FIC_           "cpl" // Control panel file (Windows 3.x)

#define EXT_FIC_           "cpo" // Corel Print House file

#define EXT_FIC_           "cps" // Backup of startup files by Central Point PC Tools autoexec.cps

#define EXT_FIC_           "cpt" // Compressed Mac file archive created by COMPACT PRO (ext-pc.zip)



#define EXT_FIC_           "cpx" // Control Panel Applet

#define EXT_FIC_           "cpy" // Copy Books Data file
#define EXT_FIC_           "cpz" // Music text file (COMPOZ)
#define EXT_FIC_           "crd" // Cardfile (Windows 3.x - YourWay)


#define EXT_FIC_           "crf" // Cross-reference (MS MASM - Zortech C++)
#define EXT_FIC_           "crh" // Links Games Course file

#define EXT_FIC_           "crp" // Encrypted database (dBASE IV)
#define EXT_FIC_           "crs" // File Conversion Resource (WordPerfect 5.1)
#define EXT_FIC_           "crt" // Terminal settings information (Oracle)
#define EXT_FIC_           "crtr" // Multi-Ad Creator 7 document.cruCompressed file archive created by CRUSH
#define EXT_FIC_           "crx" // Links Games Course file
#define EXT_FIC_           "crz" // Links Games Course file
#define EXT_FIC_           "csa" // Comma Deliminated Text

#define EXT_FIC_           "csf" // Van Dyke's CRT/SecureCRT Script file
#define EXT_FIC_           "csg" // Graph (Statistica/w)
#define EXT_FIC_           "csh" // Hamilton Labs C Shell Script file
#define EXT_FIC_           "csk" // Claris Works
#define EXT_FIC_           "csm" // Precompiled headers (Borland C++ 4.5)
#define EXT_FIC_           "csp" // Pc Emcee Screen Image file (Computer Support Corporation)
#define EXT_FIC_           "css" // Datafile (CSS - Stats+)

#define EXT_FIC_           "cst" // Macromedia Director Cast file
#define EXT_FIC_           "csv" // Comma Separated Values text file format (ASCII)

#define EXT_FIC_           "ctc" // Control file (PC Installer)
#define EXT_FIC_           "ctd" // Cobra Track Dump



#define EXT_FIC_           "ctf" // Character code translation file (Symphony)
#define EXT_FIC_           "ctg" // Cartridge Definition file


#define EXT_FIC_           "ctl" // Control file (dBASE IV - Aldus Setup)

#define EXT_FIC_           "ctt" // Labview file
#define EXT_FIC_           "ctx" // Course TeXt file (Microsoft online guides)

#define EXT_FIC_           "cty" // SimCity City file
#define EXT_FIC_           "cue" // MS Cue Cards data
#define EXT_FIC_           "cuf" // C Utilities Form definition (TCU Turbo C Utilities)
#define EXT_FIC_           "cul" // Windows cursor library (IconForge, ImageForge, ImageForge PRO)
#define EXT_FIC_           "cur" // Cursor image file (Windows 3.x)
#define EXT_FIC_           "cut" // Bitmap graphics (Dr. Halo)
#define EXT_FIC_           "cv4" // Color file (CodeView)
#define EXT_FIC_           "cv5" // Canvas version 5
#define EXT_FIC_           "cva" // Compaq Diagnostics
#define EXT_FIC_           "cvb" // Borland BDE File
#define EXT_FIC_           "cvp" // Cover page (WinFax)
#define EXT_FIC_           "cvr" // WinFax Cover Sheet

#define EXT_FIC_           "cvs" // Graphics (Canvas)
#define EXT_FIC_           "cvt" // Backup file for CONVERTed database file (dBASE IV)
#define EXT_FIC_           "cvw" // Color file (CodeView)

#define EXT_FIC_           "cwk" // Claris Works data
#define EXT_FIC_           "cwz" // CropWalker file
#define EXT_FIC_           "cxp " // Core Media Player XML-based Playlist File 
#define EXT_FIC_           "cxt" // Macromedia Director Protected Cast file
#define EXT_FIC_           "cxx" // C++ source code file (Zortech C++)
#define EXT_FIC_           "d00" // Blaster Master Pro File 

#define EXT_FIC_           "d2s" // Character file (Diablo 2)
#define EXT_FIC_           "d3d " // File Extension for Desktop-3D Notes 

#define EXT_FIC_           "d64" // Commodore 64 Emulator Disk Image
#define EXT_FIC_           "dat" // Data file in special format or ASCII





#define EXT_FIC_           "day" // Journal file.db Configuration (dBASE IV - dBFast)

#define EXT_FIC_           "db$" // Temperature debug info (Clarion Modula-2)

#define EXT_FIC_           "db2" // Database (dBASE II)
#define EXT_FIC_           "db3" // Database (dBASE III)
#define EXT_FIC_           "dba" // Datafile (DataEase)
#define EXT_FIC_           "dbb" // ANSYS Database Backup

#define EXT_FIC_           "dbd" // Business data (Business Insight)


#define EXT_FIC_           "dbg" // Symbolic debugging information (MS C/C++)
#define EXT_FIC_           "dbk" // Database backup (dBASE IV)
#define EXT_FIC_           "dbl" // Windows XP Activation file
#define EXT_FIC_           "dbm" // Datafile (DataEase)


#define EXT_FIC_           "dbo" // Compiled program (dBASE IV)
#define EXT_FIC_           "dbs" // Database in SQL Windows format


#define EXT_FIC_           "dbt" // Data Base Text (Clipper)


#define EXT_FIC_           "dbw" // Windows file (DataBoss)
#define EXT_FIC_           "dbx" // Database


#define EXT_FIC_           "dca" // Document Content Architecture text file (IBM DisplayWrite)
#define EXT_FIC_           "dcf" // Disk image file
#define EXT_FIC_           "dcm" // DCM Module Format

#define EXT_FIC_           "dcp" // Data CodePage (OS/2)
#define EXT_FIC_           "dcr" // Kodak Proprietary Image Format

#define EXT_FIC_           "dcs" // Bitmap graphics (CYMK format) (QuarkXPress)

#define EXT_FIC_           "dct" // Database dictionary (Clarion Database Developer)

#define EXT_FIC_           "dcx" // FAX Image





#define EXT_FIC_           "dd" //  Compressed Macintosh file archive created by DISKDOUBLER
#define EXT_FIC_           "ddb" // Bitmap graphics
#define EXT_FIC_           "ddc" // DivX Descriptor Description File 
#define EXT_FIC_           "ddf" // MS Data Definition Language file
#define EXT_FIC_           "ddi" // Diskdupe Image file (ddupe322.zip)
#define EXT_FIC_           "ddp" // Device Driver Profile file (OS/2)
#define EXT_FIC_           "de" // MetaProducts Download Express incompletely downloaded file
#define EXT_FIC_           "deb" // Debug script (DOS Debug)
#define EXT_FIC_           "dec" // VersaPro Declaration file
#define EXT_FIC_           "def" // Assembly header file (Geoworks)


#define EXT_FIC_           "dem" // Demonstration

#define EXT_FIC_           "des" // Description Text




#define EXT_FIC_           "dev" // Device driver
#define EXT_FIC_           "dfd" // Data Flow Diagram graphic (Prosa)
#define EXT_FIC_           "dff" // Criterion RenderWare 3.x 3D object format
#define EXT_FIC_           "dfi" // Outline font description (Digifont)
#define EXT_FIC_           "dfl" // Default program settings (Signature)

#define EXT_FIC_           "dfm" // Data Flow Diagram model file (Prosa)
#define EXT_FIC_           "dfs" // Delight Sound file
#define EXT_FIC_           "dft" // Fakt2000 file



#define EXT_FIC_           "dfv" // Printing form (Word)
#define EXT_FIC_           "dfx" // Drafix file
#define EXT_FIC_           "dgn" // Graphics (MicroStation)
#define EXT_FIC_           "dgr" // Fax Page (MS Outlook Express)

#define EXT_FIC_           "dgs" // Diagnostics
#define EXT_FIC_           "dh" //  Dependency information for .ph (Geoworks)
#define EXT_FIC_           "dhp" // Dr. Halo PIC Format graphics (Dr. Halo II - III)
#define EXT_FIC_           "dht" // Datafile (Gauss)
#define EXT_FIC_           "dia" // Diagraph graphics (Computer Support Corporation)
#define EXT_FIC_           "dib" // Bitmap graphics (Device-Independent Bitmap)
#define EXT_FIC_           "dic" // Lotus Notes / Domino dictonary file
#define EXT_FIC_           "dif" // Database (VisiCalc)


#define EXT_FIC_           "dig" // Digilink Format


#define EXT_FIC_           "dip" // Graphics
#define EXT_FIC_           "dir" // Dialing directory file (Procomm Plus)


#define EXT_FIC_           "dis" // DATAIR data import specification file



#define EXT_FIC_           "diz" // Description file (Description In Zip)
#define EXT_FIC_           "dje" // MattBatt iAM-player
#define EXT_FIC_           "dkb" // Raytraced graphics (DKBTrace)
#define EXT_FIC_           "dl" //  Animation (Italian origin)
#define EXT_FIC_           "dl_" // Compressed .dll file in an Install Archive
#define EXT_FIC_           "dld" // Data (Lotus 1-2-3)
#define EXT_FIC_           "dlg" // Dialog resource script file (MS Windows SDK)
#define EXT_FIC_           "dll" // Dynamic Link Library (Windows 3.x - OS/2)

#define EXT_FIC_           "dls" // Setup (Norton Disklock)
#define EXT_FIC_           "dmf" // Delusion/XTracker digital music file

#define EXT_FIC_           "dmg" // Macintosh OS X Disk Image file
#define EXT_FIC_           "dml" // Medical Manager DML System Script
#define EXT_FIC_           "dmo" // Demo (Derive)
#define EXT_FIC_           "dmp" // Dump file (eg. screen or memory)
#define EXT_FIC_           "dms" // Compressed Amiga file archive created by DISKMASHER
#define EXT_FIC_           "dna" // Desktop DNA data storage file 
#define EXT_FIC_           "dnasym" // Desktop DNA compiled application script 
#define EXT_FIC_           "dnax   Desktop DNA exclusion list (text) " // 
#define EXT_FIC_           "dne" // Netica Bayes net file (Norsys Software Corp.)
#define EXT_FIC_           "dng" // Dungeon file
#define EXT_FIC_           "dnl" // DigitalWebBook Electronic Book 

#define EXT_FIC_           "do " // ModelSim Filter Design HDL Coder
#define EXT_FIC_           "doc" // Document text file
#define EXT_FIC_           "dog" // Screen file (Laughing Dog Screen Maker)
#define EXT_FIC_           "doh" // Dependency information for .poh (Geoworks)
#define EXT_FIC_           "dos" // External command file (1st Reader)


#define EXT_FIC_           "dot" // Line-type definition file (CorelDRAW)

#define EXT_FIC_           "dox" // Text file (MultiMate 4.0)
#define EXT_FIC_           "doz" // Description Out of Zip (VENDINFO)
#define EXT_FIC_           "dp" //  Calendar file (Daily Planner)

#define EXT_FIC_           "dpk" // Delphi Package file
#define EXT_FIC_           "dpp" // Serif DrawPlus Drawing
#define EXT_FIC_           "dpr" // Default project- and state-related information (Borland C++)
#define EXT_FIC_           "dps" // DivX XP Skin
#define EXT_FIC_           "dpt" // Desktop DNA template 
#define EXT_FIC_           "dra" // Map Maker Pro GIS vector layer
#define EXT_FIC_           "drs" // Display Resource (WordPerfect for Win)
#define EXT_FIC_           "drv" // Device driver eg. for printer
#define EXT_FIC_           "drw" // Drawing (various)

#define EXT_FIC_           "ds4" // Vector graphics (Micrografx Designer 4.0)
#define EXT_FIC_           "dsa" // DasyTec DASYLab file
#define EXT_FIC_           "dsb" // DasyTec DASYLab file
#define EXT_FIC_           "dsc" // Discard file (Oracle)
#define EXT_FIC_           "dsd" // Database (DataShaper)
#define EXT_FIC_           "dsf" // Micrografx Designer


#define EXT_FIC_           "dsk" // Project desktop file (Borland C++ - Turbo Pascal)
#define EXT_FIC_           "dsm" // Digital sound module (DSI)
#define EXT_FIC_           "dsn" // Design (Object System Designer)
#define EXT_FIC_           "dsp" // Display parameters (Signature)


#define EXT_FIC_           "dsr" // Driver Resource (WordPerfect for Win)
#define EXT_FIC_           "dss" // Screensaver file (DCC)

#define EXT_FIC_           "dst" // PC-RDist Distribution file 

#define EXT_FIC_           "dsw" // Desktop settings (Borland C++ 4.5)
#define EXT_FIC_           "dsy" // PC Draft Symbol Library
#define EXT_FIC_           "dt_" // Data fork of a Macintosh file (Mac-ette)
#define EXT_FIC_           "dta" // Data file (Turbo Pascal - PC-File - Stata)
#define EXT_FIC_           "dtd" // SGML Document Definition file
#define EXT_FIC_           "dtf" // Database file (PFS - Q&A)
#define EXT_FIC_           "dtp" // Document (Timeworks Publisher3)

#define EXT_FIC_           "dup" // Duplicate Backup
#define EXT_FIC_           "dus" // Readiris font dictionary
#define EXT_FIC_           "dvc" // Data (Lotus 1-2-3)
#define EXT_FIC_           "dvf" // DV Studio Camcorder Graphics file
#define EXT_FIC_           "dvi" // Device Independent document (TeX)
#define EXT_FIC_           "dvp" // Desqview Program Information file (DESQview)

#define EXT_FIC_           "dvr " // DR-92 Manager file
#define EXT_FIC_           "dvr-ms" // files created by Stream Buffer Engine(SBE)
#define EXT_FIC_           "dw2" // Drawing (DesignCAD for windows)
#define EXT_FIC_           "dwc" // Compressed file archive created by DWC (dwc-a501.exe)
#define EXT_FIC_           "dwd" // Davka Writer file

#define EXT_FIC_           "dwf" // Autodesk WHIP! Drawing Web file

#define EXT_FIC_           "dwg" // Drawing (Drafix)

#define EXT_FIC_           "dwt" // AutoCAD Template/Prototype file


#define EXT_FIC_           "dx" //  Text file (DEC WPS/DX format - DEC WPS Plus)
#define EXT_FIC_           "dxf" // Drawing Interchange File Format vector graphics (AutoCAD)
#define EXT_FIC_           "dxn" // Fax (Fujitsu dexNET)
#define EXT_FIC_           "dxr" // Dependable Strengths Administrator Resources


#define EXT_FIC_           "dyc" // ICUII Videochat file
#define EXT_FIC_           "dylib " // Apple osx extension for lib
#define EXT_FIC_           "dyn" // Data (Lotus 1-2-3)
#define EXT_FIC_           "dz" // Dzip Compressed file
#define EXT_FIC_           "eap " // Enterprise Architect Project file 
#define EXT_FIC_           "ear" // Java Enterprise Application Packaging Unit
#define EXT_FIC_           "eas" // Elite Visual Basic API Spy
#define EXT_FIC_           "ebj" // Error-checking object file (Geoworks)
#define EXT_FIC_           "ebo" // MS Reader Ebook Format
#define EXT_FIC_           "ebp" // Pocket PC WindowsCE Project file
#define EXT_FIC_           "ecf" // WinFax Office Add-in file
#define EXT_FIC_           "eco" // NetManage ECCO file
#define EXT_FIC_           "ecw" // Ensoniq Waveset Format

#define EXT_FIC_           "edb" // MS Exchange Database

#define EXT_FIC_           "edl" // Edit Decision List (management for video/film post production)
#define EXT_FIC_           "eds" // Ensoniq SQ80 disk image
#define EXT_FIC_           "edt" // Default settings (VAX Edt editor)
#define EXT_FIC_           "eeb" // Button bar for Equation Editor (WordPerfect for Win)
#define EXT_FIC_           "efe" // Ensoniq EPS file
#define EXT_FIC_           "eft" // High resolution screen font (ChiWriter)
#define EXT_FIC_           "efx" // Fax (Everex EFax)
#define EXT_FIC_           "ega" // EGA display font (Ventura Publisher)
#define EXT_FIC_           "ek5" // SonarData Echoview file
#define EXT_FIC_           "ek6" // SonarData Echoview file
#define EXT_FIC_           "ekm" // EXP: The Scientific Word Processor Macro
#define EXT_FIC_           "el" //  Elisp source code file (Emacs lisp)
#define EXT_FIC_           "elc" // Compiled ELISP code (Emacs lisp)
#define EXT_FIC_           "elm" // MS FrontPage Theme-Pack file 
#define EXT_FIC_           "elt" // Event list text file (Prosa)
#define EXT_FIC_           "email" // Outlook Express Mail Message
#define EXT_FIC_           "emb" // Everest Embedded Bank File
#define EXT_FIC_           "emd" // ABT Extended Module
#define EXT_FIC_           "emf" // Enchanced Metafile graphics
#define EXT_FIC_           "eml" // MS Outlook Express Electronic Mail

#define EXT_FIC_           "emp" // E-Music File Format
#define EXT_FIC_           "ems" // PC Tools Enhanced Menu System Config
#define EXT_FIC_           "emu" // Terminal emulation data (BITCOM)
#define EXT_FIC_           "emx" // Ensuredmail encrypted file/e-mail message
#define EXT_FIC_           "enc" // Encoded file - UUENCODEd file (Lotus 1-2-3 - uuexe515.exe)

#define EXT_FIC_           "end" // Arrow-head definition file (CorelDRAW)
#define EXT_FIC_           "eng" // Dictionary engine (Sprint)

#define EXT_FIC_           "ens" // EndNote Styles file
#define EXT_FIC_           "env" // Enveloper macro (WOPR)

#define EXT_FIC_           "eot" // MS WEFT Embedded OpenType file
#define EXT_FIC_           "epd" // Publication (Express Publisher)
#define EXT_FIC_           "epf " // Encryption Protection (encrypted file format)

#define EXT_FIC_           "epi" // Document (Express Publisher)
#define EXT_FIC_           "epp" // EditPad Pro Project
#define EXT_FIC_           "eps" // Encapsulated PostScript vector graphics (Adobe Illustrator)

#define EXT_FIC_           "eqn" // Equation (WordPerfect for Win)
#define EXT_FIC_           "erd" // Entity Relationship Diagram graphic file (Prosa)
#define EXT_FIC_           "erm" // Entity Relationship Diagram model file (Prosa)
#define EXT_FIC_           "err" // Error log

#define EXT_FIC_           "esh" // Extended Shell batch file
#define EXT_FIC_           "esl" // MS Visual FoxPro Distributable Support Library
#define EXT_FIC_           "esp" // Ventura file
#define EXT_FIC_           "ess" // EXP: The Scientific Word Processor Style Sheet
#define EXT_FIC_           "est" // MS Streets & Trips 2001 Trip file
#define EXT_FIC_           "etf" // Enriched Text file

#define EXT_FIC_           "eth" // Document (Ethnograph 3)
#define EXT_FIC_           "etx" // Structure Enhanced (setext) text
#define EXT_FIC_           "ev" // SonarData Echoview file
#define EXT_FIC_           "evi" // SonarData Echoview file
#define EXT_FIC_           "evl" // SonarData Echoview file
#define EXT_FIC_           "evr" // SonarData Echoview file
#define EXT_FIC_           "evt" // Event log
#define EXT_FIC_           "evy" // Document (WordPerfect Envoy)
#define EXT_FIC_           "ewd" // Document (Express Publisher for Windows)
#define EXT_FIC_           "ewl" // EclipseCrossword Word List

#define EXT_FIC_           "ex_" // Compressed .EXE File in an Install Archive
#define EXT_FIC_           "ex3" // Device driver (Harvard Graphics 3.0)
#define EXT_FIC_           "exc" // Rexx source code file (VM/CMS)

#define EXT_FIC_           "exd" // Control Information Cache
#define EXT_FIC_           "exe" // Directly executable program (DOS)
#define EXT_FIC_           "exm" // Msdos executable, system-manager compliant (HP calculator)
#define EXT_FIC_           "exp" // ICQ Saved Chat file
#define EXT_FIC_           "ext" // Extension file (Norton Commander)
#define EXT_FIC_           "exx" // Intermediate file by MsgPut (IBM LinkWay)
#define EXT_FIC_           "ezf" // Fax (Calculus EZ-Fax)
#define EXT_FIC_           "ezm" // Text file 
#define EXT_FIC_           "ezp" // Edify Electronic Workforce Backup Utility
#define EXT_FIC_           "f" //   Fortran source code file

#define EXT_FIC_           "f01" // Fax (perfectfax)
#define EXT_FIC_           "f06" // Dos screen text font - height 6 pixels (fntcol13.zip)
#define EXT_FIC_           "f07" // Dos screen text font - height 7 pixels (fntcol13.zip)
#define EXT_FIC_           "f08" // Dos screen text font - height 8 pixels (fntcol13.zip)
#define EXT_FIC_           "f09" // Dos screen text font - height 9 pixels (fntcol13.zip)
#define EXT_FIC_           "f10" // Dos screen text font - height 10 pixels (fntcol13.zip)
#define EXT_FIC_           "f11" // Dos screen text font - height 11 pixels (fntcol13.zip)
#define EXT_FIC_           "f12" // Dos screen text font - height 12 pixels (fntcol13.zip)
#define EXT_FIC_           "f13" // Dos screen text font - height 13 pixels (fntcol13.zip)
#define EXT_FIC_           "f14" // Dos screen text font - height 14 pixels (fntcol13.zip)
#define EXT_FIC_           "f16" // Dos screen text font - height 16 pixels (fntcol13.zip)
#define EXT_FIC_           "f2" // FLASH BIOS file
#define EXT_FIC_           "f2r" // Linear module (music) (Farandole)
#define EXT_FIC_           "f3r" // Blocked module (music) (Farandole)
#define EXT_FIC_           "f77" // Fortran 77 source code file
#define EXT_FIC_           "f90" // Fortran file
#define EXT_FIC_           "f96" // Fax (Frecom FAX96)
#define EXT_FIC_           "fac" // Face graphics
#define EXT_FIC_           "faq" // Frequently Asked Questions text file
#define EXT_FIC_           "far" // Farandoyle Tracker Music Module

#define EXT_FIC_           "fav" // MS Outlook Bar Shortcuts
#define EXT_FIC_           "fax" // Fax (raster graphics) (most Fax programs)
#define EXT_FIC_           "fbc" // FamilyTree Compressed backup file
#define EXT_FIC_           "fbk" // Navison Financials Backup

#define EXT_FIC_           "fc" //  Spell checking dictionary (Harvard Graphics 2.0)
#define EXT_FIC_           "fcd" // Virtual CD-ROM



#define EXT_FIC_           "fcm" // Binary file patch file (forward compression)(jlpak10.zip)
#define EXT_FIC_           "fcp" // FLAMES Checkpoint Restart file (Ternion)
#define EXT_FIC_           "fcs" // Flow Cytometry Standard Format






#define EXT_FIC_           "fcw" // Campaign Cartographer 2 file
#define EXT_FIC_           "fd" //  Declaration file (MS Fortran)

#define EXT_FIC_           "fdb" // Art Explosion Portfolio Catalog file


#define EXT_FIC_           "fdf" // Adobe Acrobat Forms document
#define EXT_FIC_           "fdr" // Final Draft Document file

#define EXT_FIC_           "fdw" // Form (F3 Design and Mapping)
#define EXT_FIC_           "feb" // Button bar for Figure Editor (WordPerfect for Win)
#define EXT_FIC_           "fes" // Fabio Editing Software
#define EXT_FIC_           "ff" //  Outline font description (Agfa Compugraphics)
#define EXT_FIC_           "ffa" // MS Fast Find file
#define EXT_FIC_           "fff" // Fax (defFax)
#define EXT_FIC_           "ffl" // MS Fast Find file
#define EXT_FIC_           "ffo" // MS Fast Find file
#define EXT_FIC_           "fft" // Dca/FFT Final Form Text text file (DisplayWrite)
#define EXT_FIC_           "ffx" // Microsoft Fast Find file
#define EXT_FIC_           "fgd" // Folder Guard Data


#define EXT_FIC_           "fh3" // Vector graphics (Aldus FreeHand 3.x)
#define EXT_FIC_           "fh4" // Vector graphics (Aldus FreeHand 4.x)
#define EXT_FIC_           "fh5" // Freehand 5
#define EXT_FIC_           "fh6" // Freehand 6
#define EXT_FIC_           "fh7" // Freehand 7
#define EXT_FIC_           "fh8" // Macromedia Freehand 8
#define EXT_FIC_           "fh9" // Macromedia Freehand 9
#define EXT_FIC_           "fh10" // Macromedia Freehand 10
#define EXT_FIC_           "fi" //  Interface file (MS Fortran)
#define EXT_FIC_           "fif" // Fractal Image Format file
#define EXT_FIC_           "fig" // REND386/AVRIL Graphic

#define EXT_FIC_           "fil" // File template (Application Generator)


#define EXT_FIC_           "fin" // Print-formatted text file (Perfect Writer - Scribble - MINCE)
#define EXT_FIC_           "fit" // Fits graphics

#define EXT_FIC_           "fix" // Patch file
#define EXT_FIC_           "fky" // Macro file (FoxPro)
#define EXT_FIC_           "fla" // Macromedia Flash
#define EXT_FIC_           "flb" // Format library (Papyrus)
#define EXT_FIC_           "flc" // Animation (Autodesk Animator)
#define EXT_FIC_           "fld" // Folder (Charisma)
#define EXT_FIC_           "flf" // Corel Paradox Form
#define EXT_FIC_           "fli" // Tex font library (EmTeX)

#define EXT_FIC_           "flm" // Film Roll (AutoCAD/AutoShade)
#define EXT_FIC_           "flo" // Micrografx FlowCharter
#define EXT_FIC_           "flp" // FlipAlbum file

#define EXT_FIC_           "flt" // Asymetrix Graphics Filter Support file

#define EXT_FIC_           "flv" // Macromedia Flash Video file
#define EXT_FIC_           "flx" // Compiled binary (DataFlex)
#define EXT_FIC_           "fm" //  Spreatsheet (FileMaker Pro)
#define EXT_FIC_           "fm1" // Spreadsheet (Lotus 1-2-3 release 2.x)
#define EXT_FIC_           "fm3" // Device driver (Harvard Graphics 3.0)

#define EXT_FIC_           "fmb" // File Manager Button bar (WordPerfect for Win)
#define EXT_FIC_           "fmf" // Font or icon file (IBM LinkWay)
#define EXT_FIC_           "fmg" // FreeMarkets Graphics Browser
#define EXT_FIC_           "fmk" // Makefile (Fortran PowerStation)
#define EXT_FIC_           "fmo" // Compiled format file (dBASE IV)
#define EXT_FIC_           "fmp" // FileMaker Pro Document
#define EXT_FIC_           "fmt" // Format file (dBASE IV - FoxPro - Clipper 5 - dBFast)

#define EXT_FIC_           "fmv" // Frame Vector Metafile
#define EXT_FIC_           "fmz" // Form Z Program files (drawing program)
#define EXT_FIC_           "fn3" // Font file (Harvard Graphics 3.0)
#define EXT_FIC_           "fnt" // Font file (many)
#define EXT_FIC_           "fnx" // Inactive font (Exact)
#define EXT_FIC_           "fo1" // Font file (Borland Turbo C)
#define EXT_FIC_           "fo2" // Font file (Borland Turbo C)
#define EXT_FIC_           "fol" // Folder of saved messages (1st Reader)
#define EXT_FIC_           "fon" // Dialing directory file (Telix)
#define EXT_FIC_           "for" // Fortran source code file
#define EXT_FIC_           "fot" // Installed Truetype font (Windows Font Installer)
#define EXT_FIC_           "fp" //  Configuration file (FoxPro)
#define EXT_FIC_           "fp3" // FileMaker Pro 3.0 and earlier files
#define EXT_FIC_           "fp4" // FileMaker Pro 4.0
#define EXT_FIC_           "fp5" // FileMaker Pro 5.0 and later files 
#define EXT_FIC_           "fpb" // FLAMES Playback file (Ternion)
#define EXT_FIC_           "fpc" // Catalog (FoxPro)
#define EXT_FIC_           "fpk" // JetForm FormFlow file
#define EXT_FIC_           "fpr" // FLAMES Prototype file (Ternion)
#define EXT_FIC_           "fpt" // Memo (FoxPro)
#define EXT_FIC_           "fpw" // Floorplan drawing (FloorPLAN plus for Windows)
#define EXT_FIC_           "fpx" // FlashPix Bitmap
#define EXT_FIC_           "fqy" // FLAMES FLARE Command file (Ternion)
#define EXT_FIC_           "fr3" // Renamed dBASE III+ form file (dBASE IV)
#define EXT_FIC_           "frc" // FLAMES RECORD Output file; FLARE Input file (Ternion)
#define EXT_FIC_           "fre" // Creative Digital Blaster Digital VCR file

#define EXT_FIC_           "frf" // Font (FontMonger)
#define EXT_FIC_           "frg" // Uncompiled report file (dBASE IV)
#define EXT_FIC_           "frl" // FormFlow file
#define EXT_FIC_           "frm" // Form (Visual Basic)


#define EXT_FIC_           "fro" // Compiled report file (dBASE IV)
#define EXT_FIC_           "frp" // Form (PerForm PRO Plus - FormFlow)
#define EXT_FIC_           "frs" // Screen Font Resource (WordPerfect for Win)
#define EXT_FIC_           "frt" // Report memo (FoxPro)
#define EXT_FIC_           "frx" // Report (FoxPro)

#define EXT_FIC_           "fsc" // FLAMES Scenario file (Ternion)
#define EXT_FIC_           "fsh" // EA Sports Game Graphic Editor file
#define EXT_FIC_           "fsl" // Form (Paradox for Windows)
#define EXT_FIC_           "fsm" // Farandoyle Sample format music
#define EXT_FIC_           "fst" // Linkable program (dBFast)
#define EXT_FIC_           "fsx" // Data (Lotus 1-2-3)
#define EXT_FIC_           "fsy" // Fileware's Filesync
#define EXT_FIC_           "ftm" // Font file (Micrografx)
#define EXT_FIC_           "fts" // Windows Help Full-Text Search Index file
#define EXT_FIC_           "ftw" // Family file

#define EXT_FIC_           "ftp" // Configuration (FTP Software PC/TCP)
#define EXT_FIC_           "fvt" // Interlock Public Computer Utility
#define EXT_FIC_           "fw" //  Database (FrameWork)
#define EXT_FIC_           "fw2" // Database (Framework II)
#define EXT_FIC_           "fw3" // Database (Framework III)
#define EXT_FIC_           "fx" //  On-line guide (FastLynx)
#define EXT_FIC_           "fxd" // Phonebook (FAXit)
#define EXT_FIC_           "fxm" // WinFax/WinFax MiniViewer Fax
#define EXT_FIC_           "fxo" // Fax Image Document
#define EXT_FIC_           "fxp" // Compiled format (FoxPro)
#define EXT_FIC_           "fxr" // WinFax Received Document
#define EXT_FIC_           "fxs" // Fax Transmit Format graphics (WinFax)
#define EXT_FIC_           "g" //   Data chart (APPLAUSE)
#define EXT_FIC_           "g3f" // Zetafax TIFF file (fine resolution)
#define EXT_FIC_           "g3n" // Zetafax TIFF file (normal resolution)
#define EXT_FIC_           "g8" //  Raw graphics (one byte per pixel) plane three (PicLab)
#define EXT_FIC_           "gal" // Corel Multimedia Manager Album
#define EXT_FIC_           "gam" // Fax (GammaFax)
#define EXT_FIC_           "gat" // Gator file
#define EXT_FIC_           "gb" // GameBoy ROM
#define EXT_FIC_           "gba" // Game Boy Advanced ROM

#define EXT_FIC_           "gbc" // Game Boy COlor ROM
#define EXT_FIC_           "gbd" // Gator Banner file
#define EXT_FIC_           "gbl" // Global definitions (VAXTPU editor)
#define EXT_FIC_           "gbr" // GIMP Brush file

#define EXT_FIC_           "gbx" // Gerber file 
#define EXT_FIC_           "gc1" // Lisp source code (Golden Common Lisp 1.1)
#define EXT_FIC_           "gc3" // Lisp source code (Golden Common Lisp 3.1)
#define EXT_FIC_           "gcd" // Graphics
#define EXT_FIC_           "gdb" // Interbase Database

#define EXT_FIC_           "gdf" // Dictionary file (GEOS)
#define EXT_FIC_           "gdr" // Bitmap Font file (SymbianOS)
#define EXT_FIC_           "ged" // Editor's native file format (Arts & Letters)
#define EXT_FIC_           "gem" // Vector graphics (GEM - Ventura Publisher)
#define EXT_FIC_           "gen" // Compiled template (dBASE Application Generator)


#define EXT_FIC_           "geo" // Geode (Geoworks)
#define EXT_FIC_           "gfb" // Compressed GIF image created by GIFBLAST (gifblast.exe)
#define EXT_FIC_           "gft" // Font (NeoPaint)
#define EXT_FIC_           "gfx" // Genigraphics Graphics Link Presentation
#define EXT_FIC_           "gho" // Symantec Ghost Disk image file
#define EXT_FIC_           "ghs" // Lasertank High Scores

#define EXT_FIC_           "gib" // Chart (Graph-in-the-Box)
#define EXT_FIC_           "gid" // Windows Help index file
#define EXT_FIC_           "gif" // Graphics Interchange Format bitmap graphics (CompuShow)
#define EXT_FIC_           "gig" // Sound file
#define EXT_FIC_           "giw" // Presentation (Graph-in-the-Box for Windows)
#define EXT_FIC_           "gl" //  Animation (GRASP GRAphical System for Presentation)
#define EXT_FIC_           "glm" // Datafile (Glim)
#define EXT_FIC_           "gls" // Datafile (Across)
#define EXT_FIC_           "gly" // Glossary (MS Word)
#define EXT_FIC_           "gmf" // CGM graphics (APPLAUSE)
#define EXT_FIC_           "gmp" // Geomorph tile map (SPX)
#define EXT_FIC_           "gno" // Genopro Genealogy Document file
#define EXT_FIC_           "goc" // Goc source code file (Geoworks)
#define EXT_FIC_           "goh" // Goc header file (Geoworks)
#define EXT_FIC_           "gp" //  Geode parameter file (Geoworks Glue)
#define EXT_FIC_           "gp3" // CCITT Group 3 file

#define EXT_FIC_           "gpd" // VISUAL EPR Input Data for PARAMS.EXE
#define EXT_FIC_           "gph" // Graph (Lotus 1-2-3/G)
#define EXT_FIC_           "gpk" // Omnigo program package
#define EXT_FIC_           "gr2" // Screen driver (Windows 3.x)
#define EXT_FIC_           "gra" // Datafile (SigmaPlot)
#define EXT_FIC_           "grb" // Ms-DOS Shell Monitor file (MS-DOS 5)
#define EXT_FIC_           "grd" // Gradebook Power file

#define EXT_FIC_           "grf" // Graph file (Graph Plus - Charisma)
#define EXT_FIC_           "grl" // Matlab Graphic Format
#define EXT_FIC_           "grp" // Group file (Windows 3.x - Papyrus)

#define EXT_FIC_           "grx" // File list (GetRight)
#define EXT_FIC_           "gry" // Raw GREY graphics
#define EXT_FIC_           "gs1" // Presentation (GraphShow)
#define EXT_FIC_           "gsd" // Vector graphics (Professional Draw)

#define EXT_FIC_           "gsm" // Raw GSM 6.10 Audio Stream


#define EXT_FIC_           "gsp" // Geometer's Sketchpad Material file
#define EXT_FIC_           "gsw" // Worksheet (GraphShow)
#define EXT_FIC_           "gtp" // GuitarPro file
#define EXT_FIC_           "gts" // Genome Software Tempo Alarm Clock
#define EXT_FIC_           "gup" // Data (PopMail)
#define EXT_FIC_           "gwi" // Groupwise File
#define EXT_FIC_           "gwp" // Greetings WorkShop file
#define EXT_FIC_           "gxd" // General CADD Pro file


#define EXT_FIC_           "gxl" // Graphics library (Genus)
#define EXT_FIC_           "gxt" // GTA2 Game file
#define EXT_FIC_           "gym" // Sega Genesis Music Logged Format
#define EXT_FIC_           "h!" //  On-line help file (Flambeaux Help! Display Engine)
#define EXT_FIC_           "h++" // Header file (C++)
#define EXT_FIC_           "h--" // Header file (Sphinx C--)
#define EXT_FIC_           "ha" //  Compressed file archive created by HA (ha098.zip)
#define EXT_FIC_           "ham" // Image file
#define EXT_FIC_           "hap" // Compressed file archive created by HAP (hap303re.zip)
#define EXT_FIC_           "hbk" // Handbook (Mathcad)
#define EXT_FIC_           "hbs " // eBerry Transparent Animation - compressed bitmap files
#define EXT_FIC_           "hcr" // IBM HCD/HCM Production Configuration
#define EXT_FIC_           "hdf" // Hierarchical Data File graphics (SDSC Image Tools)

#define EXT_FIC_           "hdl" // Alternate download file listing (Procomm Plus)
#define EXT_FIC_           "hdp" // Magix Music/Video
#define EXT_FIC_           "hdr" // Pc-File+ Database header


#define EXT_FIC_           "hdw" // Vector graphics (Harvard Draw)
#define EXT_FIC_           "hdx" // Help index (AutoCAD - Zortech C++)
#define EXT_FIC_           "hex" // Hex dump
#define EXT_FIC_           "hfi" // Hp Font Info file (GEM)
#define EXT_FIC_           "hfx" // HotFax file

#define EXT_FIC_           "hgl" // Hp Graphics Language graphics
#define EXT_FIC_           "hh" //  C++ header file
#define EXT_FIC_           "hhc" // Table of Contents file

#define EXT_FIC_           "hhh" // Precompiled header file (Power C)
#define EXT_FIC_           "hhk" // Help Workshop Index file
#define EXT_FIC_           "hhp" // Help information for remote users (Procomm Plus)
#define EXT_FIC_           "hht" // MS Messenger file
#define EXT_FIC_           "hin" // Molecule (HyperChem)
#define EXT_FIC_           "his" // Insight II Dynamics Trajectory History file

#define EXT_FIC_           "hlb" // Help library (VAX)
#define EXT_FIC_           "hlp" // Help information
#define EXT_FIC_           "hlz" // Multi-Edit Packed Help file
#define EXT_FIC_           "hm3 " // Help & Manual 3 project Format
#define EXT_FIC_           "hmm" // Alternate Mail Read option menu (Procomm Plus)
#define EXT_FIC_           "hnc" // CNC program files Heidenhain (?) dialog
#define EXT_FIC_           "hof" // Hall Of Fame (game scores)
#define EXT_FIC_           "hp8" // Ascii text HP Roman8 character set (NewWave Write)
#define EXT_FIC_           "hpf" // Hp LaserJet fonts (PageMaker)
#define EXT_FIC_           "hpg" // HPGL plotter file vector graphics (AutoCad - Harvard Graphics)
#define EXT_FIC_           "hpi" // Font information file (GEM)
#define EXT_FIC_           "hpj" // Help project (MS Help Compiler)
#define EXT_FIC_           "hpk" // Compressed file archive created by HPACK (hpack75.zip)
#define EXT_FIC_           "hpm" // Emm text (HP NewWave)

#define EXT_FIC_           "hpp" // C++ header file (Zortech C++)
#define EXT_FIC_           "hqx" // Compressed Macintosh ASCII archive created by BINHEX (xbin23.zip)
#define EXT_FIC_           "hrf" // Graphics (Hitachi Raster Format)
#define EXT_FIC_           "hrm" // Alternate Main menu for limited/normal users (Procomm Plus)
#define EXT_FIC_           "hs2" // Monochrome image (Postering)
#define EXT_FIC_           "hsi" // Handmade Software Inc. graphics - almost JPEG (Image Alchemy)
#define EXT_FIC_           "hst" // History file (Procomm Plus)
#define EXT_FIC_           "hta" // Hypertext application
#define EXT_FIC_           "htc" // HTML Component (mechanism for implementing Dynamic HTML in script)
#define EXT_FIC_           "htf" // WebBase File
#define EXT_FIC_           "hti" // WebBase File
#define EXT_FIC_           "htr" // Motion Analysis Software Skeletal file
#define EXT_FIC_           "htt" // Hypertext template
#define EXT_FIC_           "htx" // Hypertext file
#define EXT_FIC_           "hus" // Husqvarna Designer I Embroidery Machine Format
#define EXT_FIC_           "hwd" // Presentation (Hollywood)
#define EXT_FIC_           "hxm" // Alternate Protocol Selection menu for all users (Procomm Plus)
#define EXT_FIC_           "hxx" // C++ header file
#define EXT_FIC_           "hy1" // Hyphenation algorithms (Ventura Publisher)
#define EXT_FIC_           "hy2" // Hyphenation algorithms (Ventura Publisher)
#define EXT_FIC_           "hyc" // Data (WordPerfect)
#define EXT_FIC_           "hyd" // Hyphenation dictionary (WordPerfect for Win)
#define EXT_FIC_           "hyp" // Compressed file archive created by HYPER (hyper25.zip)
#define EXT_FIC_           "hyt " // VFSMOD Project output file
#define EXT_FIC_           "i" //   Intermediate file (Borland C++ 4.5)
#define EXT_FIC_           "iaf" // MS Outlook 97 and 2000 e-mail account settings
#define EXT_FIC_           "iax" // Bitmap graphics (IBM Image Access eXecutive)
#define EXT_FIC_           "ibm" // Compressed file archive created by ARCHDOS (Internal IBM only)
#define EXT_FIC_           "ica" // Bitmap graphics (Image Object Content Architecture)
#define EXT_FIC_           "icb" // Bitmap graphics
#define EXT_FIC_           "icc" // Kodak Printer Image

#define EXT_FIC_           "icd" // IronCAD 2D CAD file
#define EXT_FIC_           "icl" // icon library (ActivIcons, IconForge, ImageForge, ImageForge PRO)
#define EXT_FIC_           "icm" // Image Color Matching Profile file

#define EXT_FIC_           "icn" // Icon source code file
#define EXT_FIC_           "ico" // Icon (Windows 3.x)
#define EXT_FIC_           "id" //  Disk identification file
#define EXT_FIC_           "idb" // Database Used by Disassembler

#define EXT_FIC_           "ide" // Project (Borland C++ 4.5)
#define EXT_FIC_           "idf" // ARTiSAN Real-time Studio ID file


#define EXT_FIC_           "idw" // Vector graphics (IntelliDraw)
#define EXT_FIC_           "idx" // Index (many - FoxPro)
#define EXT_FIC_           "ies" // Photometric file data 
#define EXT_FIC_           "ifd" // Form (JetForm Design)
#define EXT_FIC_           "iff" // Interchange File Format bitmap graphics/sound (Amiga)

#define EXT_FIC_           "ifo" // Saved graphic objects (ImageForge PRO)
#define EXT_FIC_           "ifp" // Script (KnowledgeMan)
#define EXT_FIC_           "ifs" // Fractal image compressed file (Yuvpak)

#define EXT_FIC_           "igr" // Intergraph SmartSketch Drawing
#define EXT_FIC_           "igs" // IGES-Format
#define EXT_FIC_           "igx" // iGrafx Process
#define EXT_FIC_           "iif" // QuickBooks for Windows Interchange file
#define EXT_FIC_           "ilb" // Data (Scream Tracker)
#define EXT_FIC_           "ilk" // Outline of program's format (MS ILink incremental linker)
#define EXT_FIC_           "im30" // Sun Raster image file
#define EXT_FIC_           "im8" // Sun raster graphics
#define EXT_FIC_           "ima" // Mirage vector graphics (EGO, Chart, Autumn)
#define EXT_FIC_           "imb" // IncrediMail file
#define EXT_FIC_           "imc" // IncrediMail file
#define EXT_FIC_           "imf" // ImageForge/IconForge saved filtered brushes(IconForge, ImageForge, ImageForge PRO)
#define EXT_FIC_           "img" // Bitmap graphics (Ventura Publisher - GEM Paint)
#define EXT_FIC_           "imm" // IncrediMail Trash
#define EXT_FIC_           "imn" // IncrediMail Notifier
#define EXT_FIC_           "imp" // Spreadsheet (Lotus Improv)

#define EXT_FIC_           "imq" // Image presentation (ImageQ)
#define EXT_FIC_           "ims" // Incredimail Graphic
#define EXT_FIC_           "imv" // Yahoo Instant Messenger IMVironment

#define EXT_FIC_           "imw" // Imageware Surfacer 3D CAD Surface Geometry

#define EXT_FIC_           "imz" // Compressed floppy image
#define EXT_FIC_           "in$" // Installation file (HP NewWave)
#define EXT_FIC_           "in3" // Input device driver (Harvard Graphics 3.0)
#define EXT_FIC_           "inb" // Test script (Vermont HighTest)
#define EXT_FIC_           "inc" // Include file (several programming languages)
#define EXT_FIC_           "ind" // Index (dBASE IV)
#define EXT_FIC_           "inf" // Type 1 LaserJet font information file (soft font installers)


#define EXT_FIC_           "ini" // Initialization file
#define EXT_FIC_           "ink" // Pantone reference fills file (CorelDRAW)
#define EXT_FIC_           "inl" // MS Visual C++ Inline Function file
#define EXT_FIC_           "inp" // GIS Software Text Input file  


#define EXT_FIC_           "ins" // Data (WordPerfect)


#define EXT_FIC_           "int" // Borland Interface Units

#define EXT_FIC_           "inv" // Rogue Spear Inventory file
#define EXT_FIC_           "inx" // Index (Foxbase)
#define EXT_FIC_           "io" //  Compressed file archive created by CPIO
#define EXT_FIC_           "iob" // 3d graphics database in TDDD format
#define EXT_FIC_           "ioc" // Organizational chart (Instant ORGcharting!)
#define EXT_FIC_           "ion" // 4dos descript.ion file (file descriptions)
#define EXT_FIC_           "ipd" // InstallPROG 6 EDBS Install Database
#define EXT_FIC_           "ipg" // Mindjongg Format
#define EXT_FIC_           "ipj" // Impatica OnCue Project file
#define EXT_FIC_           "ipl" // Pantone Spot reference palette file (CorelDRAW)
#define EXT_FIC_           "ipp" // Help & Manual Proprietary Image
#define EXT_FIC_           "ips" // Game Patch file

#define EXT_FIC_           "ipx" // IPIX AV file
#define EXT_FIC_           "ipz" // ICQ Skin Plus
#define EXT_FIC_           "irs" // Resource (WordPerfect)
#define EXT_FIC_           "isd" // Spelling Checker dictionary (RapidFile)
#define EXT_FIC_           "ish" // Compressed file archive created by ISH
#define EXT_FIC_           "isk" // Command file 
#define EXT_FIC_           "iso" // Easy CD Creator Disc Image

#define EXT_FIC_           "isr" // MS Streets & Trips Route file
#define EXT_FIC_           "iss" // InstallShield Response file

#define EXT_FIC_           "ist" // Digitrakker Instrument File (n-FaCToR)
#define EXT_FIC_           "isu" // InstallShield Uninstall Script


#define EXT_FIC_           "it" //  Settings (intalk)
#define EXT_FIC_           "itf" // Interface file (JPI TopSpeed Pascal)
#define EXT_FIC_           "ith" // InTether technology secured file
#define EXT_FIC_           "ivt" // MS Infoviewer Title
#define EXT_FIC_           "iw" //  Presentation flowchart (IconAuthor - HSC InterActive)
#define EXT_FIC_           "iwa" // Text file (IBM Writing Assistant)
#define EXT_FIC_           "iwp" // Text file (Wang)
#define EXT_FIC_           "izt" // Izl binary token file (IZL)
#define EXT_FIC_           "jar" // Java archive file
#define EXT_FIC_           "jas" // Graphics
#define EXT_FIC_           "jav" // Java source code file
#define EXT_FIC_           "jbc" // Jam Byte-Code Hex file

#define EXT_FIC_           "jbd" // Datafile (SigmaScan)
#define EXT_FIC_           "jbf" // Paint Shop Pro browser file
#define EXT_FIC_           "jbk" // Juno Backup file
#define EXT_FIC_           "jbr" // Jasc Paint Shop Pro Brush
#define EXT_FIC_           "jbx" // Project file (Project Scheduler 4)
#define EXT_FIC_           "jdt" // Accelio Capture Classic Filler
#define EXT_FIC_           "jef" // Janome NH10000 Sewing Machine file
#define EXT_FIC_           "jet" // Fax (Hybrid JetFax)
#define EXT_FIC_           "jff" // Bitmap graphics (JPEG File Interchange Format)
#define EXT_FIC_           "jfx" // J2 Fax File
#define EXT_FIC_           "jhtml" // Dynamo Server Page
#define EXT_FIC_           "jif" // JPEG/JIFF Image

#define EXT_FIC_           "jmx" // JMeter file
#define EXT_FIC_           "jnb" // Sigma Plot Workbook file
#define EXT_FIC_           "jnl" // Ingres Journal file
#define EXT_FIC_           "job" // Job file

#define EXT_FIC_           "jor" // Journal file SQL
#define EXT_FIC_           "jou" // Journal backup (VAX Edt editor)
#define EXT_FIC_           "jpc" // Graphics (Japan PIC)
#define EXT_FIC_           "jpe" // JPEG image
#define EXT_FIC_           "jpg" // Bitmap graphics (Joint Photography Experts Group)
#define EXT_FIC_           "jps" // Stereo Image
#define EXT_FIC_           "jsd" // eFAX Jet Suite Document
#define EXT_FIC_           "jsh" // Henter-Joyce, Inc. Jaws Script Header file
#define EXT_FIC_           "jsp" // Java Server page
#define EXT_FIC_           "jtf" // Fax (Hayes JT Fax)

#define EXT_FIC_           "jtp" // Jetform file
#define EXT_FIC_           "jw" //  Text document (JustWrite)
#define EXT_FIC_           "jwl" // Library (JustWrite)
#define EXT_FIC_           "jwp" // Easy CD Creator Label file

#define EXT_FIC_           "jzz" // Spreatsheet (Jazz)
#define EXT_FIC_           "k4e " // Karaoke 4 Everyone Player file 
#define EXT_FIC_           "kar" // Midi file with karaoke word track
#define EXT_FIC_           "kb" //  Keyboard script (Borland C++ 4.5)

#define EXT_FIC_           "kbd" // Keyboard mapping (LocoScript - Signature - Procomm Plus)
#define EXT_FIC_           "kbm" // Keyboard mapping (Reflection 4.0)
#define EXT_FIC_           "kcl" // Lisp source code (Kyoto Common Lisp)
#define EXT_FIC_           "kcp" // Keychamp file
#define EXT_FIC_           "kdc" // Kodak Photo-Enhancer/Photogen file
#define EXT_FIC_           "kex" // Macro (KEDIT)
#define EXT_FIC_           "key" // Datafile (Forecast Pro)


#define EXT_FIC_           "kit" // Raven Toolkit file
#define EXT_FIC_           "kix" // KixTart Script
#define EXT_FIC_           "kma" // Kodak Memory Book file
#define EXT_FIC_           "kmp" // Korg Trinity KeyMaP file
#define EXT_FIC_           "kmx" // Kaufman Mmail Warrior Mail Folder 
#define EXT_FIC_           "kos" // MicroType Pro Document
#define EXT_FIC_           "kpl" // Kazaa Playlist

#define EXT_FIC_           "kpp" // Toolpad (SmartPad)
#define EXT_FIC_           "kps" // Ibm KIPS bitmap graphics
#define EXT_FIC_           "kqe " // W32/Spybot.KQE Worm virus 
#define EXT_FIC_           "kqp" // Konica Quality Picture 
#define EXT_FIC_           "krz" // Kurzweil 2000 Sample
#define EXT_FIC_           "ktk" // Kutoka's Mia
#define EXT_FIC_           "kyb" // Keyboard mapping (FTP Software PC/TCP)
#define EXT_FIC_           "l" //   Lex source code file


#define EXT_FIC_           "l01" // ARC Digitized Raster Graphics
#define EXT_FIC_           "lab" // Datafile (NCSS - SOLO)


#define EXT_FIC_           "lat" // Crossword Express Lattice file
#define EXT_FIC_           "lay" // Word chart layout (APPLAUSE)
#define EXT_FIC_           "lbg" // Label generator data (dBASE IV)
#define EXT_FIC_           "lbl" // Label (dBASE IV - Clipper 5 - dBFast)
#define EXT_FIC_           "lbm" // Bitmap graphics (DeluxePaint)

#define EXT_FIC_           "lbo" // Compiled label (dBASE IV)
#define EXT_FIC_           "lbr" // Compressed file archive created by LU (lue220.arc)

#define EXT_FIC_           "lbt" // Label memo (FoxPro)
#define EXT_FIC_           "lbx" // Label (FoxPro)
#define EXT_FIC_           "lcf" // Linker Control File (Norton Guides compiler)
#define EXT_FIC_           "lck" // Lockfile (Paradox)
#define EXT_FIC_           "lcl" // Data (FTP Software PC/TCP)
#define EXT_FIC_           "lcn" // Lection (WordPerfect)
#define EXT_FIC_           "lcs" // Datafile (ACT! History Files)
#define EXT_FIC_           "lcw" // Spreadsheet (Lucid 3-D)
#define EXT_FIC_           "ld" //  Long Distance codes file (Telix)
#define EXT_FIC_           "ld1" // Overlay file (dBASE)
#define EXT_FIC_           "ldb" // Data (MS Access)
#define EXT_FIC_           "ldf" // Library definition file (Geoworks Glue)

#define EXT_FIC_           "leg" // Legacy Graphic Format
#define EXT_FIC_           "les" // Lesson (check *.cbt)
#define EXT_FIC_           "let" // Letter
#define EXT_FIC_           "lev" // Level file (NetHack 3.x)
#define EXT_FIC_           "lex" // Lexicon (dictionary) (many)
#define EXT_FIC_           "lfa" // LifeForm file
#define EXT_FIC_           "lft" // Laser printer font (ChiWriter)
#define EXT_FIC_           "lg" //  Logo procedure definitions (LSRHS Logo)
#define EXT_FIC_           "lgc" // Program Use Log file 
#define EXT_FIC_           "lgo" // Logo for header and footer (SuperFax)

#define EXT_FIC_           "lha" // Compressed file archive created by LHA/LHARC (lha255b.exe)
#define EXT_FIC_           "lhw" // Compressed Amiga file archive created by LHWARP
#define EXT_FIC_           "lib" // Library file (several programming languages)
#define EXT_FIC_           "lic" // License file (Shareware)
#define EXT_FIC_           "lid" // WinDVD file

#define EXT_FIC_           "lif" // Logical Interchange Format data file (Hewlett-Packard)

#define EXT_FIC_           "lim" // Compressed file archive created by LIMIT (limit12.zip)
#define EXT_FIC_           "lin" // Line types (AutoCAD)
#define EXT_FIC_           "lis" // Listing (VAX)
#define EXT_FIC_           "lit" // MS Reader EBook file
#define EXT_FIC_           "lix" // Extend Simulation Library file

#define EXT_FIC_           "lj" //  Text file for HP LJ II printer
#define EXT_FIC_           "lko" // MS Outlook Express Linked Object
#define EXT_FIC_           "ll3" // Laplink III related file (document) (LapLink III)
#define EXT_FIC_           "lmt " // RPG Maker map tree file
#define EXT_FIC_           "lnd" // 3D Landscape Data
#define EXT_FIC_           "lng" // Diablo II file

#define EXT_FIC_           "lnk" // Linker response file (.RTLink)
#define EXT_FIC_           "loc" // MicroSim PCBoard Component Locations Report

#define EXT_FIC_           "lod" // Load file
#define EXT_FIC_           "lok" // Encrypted and compressed archive format (FileWrangler, SecurDesk!, ZipWrangler)
#define EXT_FIC_           "lpc" // Printer driver (TEKO)
#define EXT_FIC_           "lpd" // Helix Nuts and Bolts File

#define EXT_FIC_           "lpf" // Lytec's Direct Electronic Medical Claims ClaimsDirect
#define EXT_FIC_           "lpi" // Live Pictures
#define EXT_FIC_           "lpk " // Licensed ActiveX Control for Internet Explorer. 
#define EXT_FIC_           "lrf" // Linker response file (MS C/C++)
#define EXT_FIC_           "lrs" // Language Resource File (WordPerfect for Win)
#define EXT_FIC_           "lsf" // Streaming Audio/Video file

#define EXT_FIC_           "lsl" // Lotus Script Library
#define EXT_FIC_           "lsp" // Lisp source code file (Xlisp)
#define EXT_FIC_           "lss" // Spreadsheet (Legato)
#define EXT_FIC_           "lst" // Keyboard macro (1st Reader)


#define EXT_FIC_           "ltm" // Form (Lotus Forms)
#define EXT_FIC_           "ltr" // Letter
#define EXT_FIC_           "lvp" // Lucent Voice Player

#define EXT_FIC_           "lwa" // LightWorks Archive Material/Scene file
#define EXT_FIC_           "lwd" // Text document (LotusWorks)
#define EXT_FIC_           "lwo" // NewTek Lightwave Object
#define EXT_FIC_           "lwp" // Lotus Wordpro 96/97 File
#define EXT_FIC_           "lwz" // MS Linguistically Enhanced Sound file
#define EXT_FIC_           "lyr" // DataCAD Layer file
#define EXT_FIC_           "lzd" // Difference file for binaries (Ldiff 1.20)
#define EXT_FIC_           "lzh" // Compressed file archive created by LHA/LHARC (lha255b.exe)
#define EXT_FIC_           "lzs" // Compressed file archive created by LARC (larc333.zip)
#define EXT_FIC_           "lzw" // Compressed Amiga file archive created by LHWARP
#define EXT_FIC_           "lzx" // Compressed file
#define EXT_FIC_           "m" //   Function (program) (Matlab)


#define EXT_FIC_           "m11" // Text file (MASS11)
#define EXT_FIC_           "m2p" // MPEG-2 Program Stream Format file
#define EXT_FIC_           "m2v" // MPEG-2 Video Only file
#define EXT_FIC_           "m3" //  Modula 3 source code file
#define EXT_FIC_           "m3d" // 3d animation macro
#define EXT_FIC_           "m3u" // Music Playlist (Winamp)
#define EXT_FIC_           "m4" //  M4 preprocessor file (unix)
#define EXT_FIC_           "m4a " // MPEG-4 Audio Layer 
#define EXT_FIC_           "m_u" // Backup of boot sector, FAT and boot dir (MazeGold)
#define EXT_FIC_           "ma3" // Macro (Harvard Graphics 3.0)
#define EXT_FIC_           "mac" // Bitmap graphics (Macintosh MacPaint)

#define EXT_FIC_           "mad" // MS Access Module Shortcut
#define EXT_FIC_           "mag" // Woody Lynn's MAG graphics format (MPS Magro Paint System)
#define EXT_FIC_           "mai" // Mail (VAX)
#define EXT_FIC_           "mak" // Makefile

#define EXT_FIC_           "man" // Command manual
#define EXT_FIC_           "map" // Color palette

#define EXT_FIC_           "mar" // Assembly program (VAX Macro)
#define EXT_FIC_           "mas" // Smartmaster set (Freelance Graphics)
#define EXT_FIC_           "mat" // Data file (Matlab)
#define EXT_FIC_           "max" // Max source code file

#define EXT_FIC_           "mb" //  Memo field values for database (Paradox)
#define EXT_FIC_           "mbf" // MS Money Backup file
#define EXT_FIC_           "mbk " // Medisoft for Windows Backup

#define EXT_FIC_           "mbx" // Mailbox (Eudora/Zerberus)
#define EXT_FIC_           "mcc" // Configuration file (Mathcad)
#define EXT_FIC_           "mcd" // Document (Mathcad)
#define EXT_FIC_           "mcf" // Mathcad font

#define EXT_FIC_           "mci" // Mci command script (Media Control Interface)
#define EXT_FIC_           "mcp" // Application script (Capsule)

#define EXT_FIC_           "mcr" // DataCAD Keyboard macro file
#define EXT_FIC_           "mcw" // Text file (MacWrite II)
#define EXT_FIC_           "mcx" // Graphic file
#define EXT_FIC_           "md" //  Compressed file archive created by MDCD (mdcd10.arc)
#define EXT_FIC_           "md5" // Message Digest 5 (Easy MD5 Creator)
#define EXT_FIC_           "mda" // Data (MS Access)
#define EXT_FIC_           "mdb" // Database (MS Access)
#define EXT_FIC_           "mdf" // Accelio Capture Classic (JetForm) Filler



#define EXT_FIC_           "mdl" // Model (3D Design Plus)

#define EXT_FIC_           "mdm" // Modem definition (TELIX)
#define EXT_FIC_           "mdmp " // Microsoft Windows XP Trouble Report
#define EXT_FIC_           "mdr" // FaxTalk Modem Doctor Modem Report file
#define EXT_FIC_           "mdt" // Data table (MS ILink incremental linker)
#define EXT_FIC_           "mdx" // Multiple index file (dBASE IV)
#define EXT_FIC_           "mdz" // MS Access Wizard Template
#define EXT_FIC_           "me" //  Usually ASCII text file READ.ME
#define EXT_FIC_           "meb" // Macro Editor bottom overflow file (WordPerfect Library)
#define EXT_FIC_           "med" // Macro Editor delete save (WordPerfect Library)

#define EXT_FIC_           "mem" // Macro Editor macro (WordPerfect Library)

#define EXT_FIC_           "meq" // Macro Editor print queue file (WordPerfect Library)
#define EXT_FIC_           "mer" // Macro Editor resident area (WordPerfect Library) (vakioalue)
#define EXT_FIC_           "mes" // Macro Editor work space file (WordPerfect Library)

#define EXT_FIC_           "met" // Macro Editor top overflow file (WordPerfect Library)

#define EXT_FIC_           "meu" // Menu group (DOS Shell)
#define EXT_FIC_           "mex" // Mex file (executable command) (Matlab)


#define EXT_FIC_           "mf" //  Metafont text file
#define EXT_FIC_           "mfx " // ImageMAKER Fax Viewer folder file
#define EXT_FIC_           "mgf" // Font (Micrografx)
#define EXT_FIC_           "mhp" // MS Home Publishing Project
#define EXT_FIC_           "mht  " // MS MHTML Document
#define EXT_FIC_           "mib" // Snmp MIB file
#define EXT_FIC_           "mic" // Microsoft Image Composer file
#define EXT_FIC_           "mid" // Standard MIDI file (music synthetizers)
#define EXT_FIC_           "mif" // Maker Interchange Format (FrameMaker)
#define EXT_FIC_           "mii" // Datafile (MicroStat-II)
#define EXT_FIC_           "mim" // MIME file
#define EXT_FIC_           "mio" // Multimedia Interactive Object
#define EXT_FIC_           "mip" // Paint Shop Pro Multiple Image Print file
#define EXT_FIC_           "mis" // Delta Force Land Warrior Mission


#define EXT_FIC_           "mix" // Object file (Power C)
#define EXT_FIC_           "mk" //  Makefile
#define EXT_FIC_           "mke" // Makefile (MS Windows SDK)
#define EXT_FIC_           "mki" // Japanese graphics MAKIchan format (MagView 0.5)
#define EXT_FIC_           "mks" // Data (TACT)
#define EXT_FIC_           "ml3" // Project (Milestones 3.x)
#define EXT_FIC_           "mlb" // Macro library file (Symphony)
#define EXT_FIC_           "mlm" // Novel Groupwise e-mail file
#define EXT_FIC_           "mm" //  Text file (MultiMate Advantage II)
#define EXT_FIC_           "mmc" // Media Catalog  

#define EXT_FIC_           "mmf" // Mail message file (MS Mail)
#define EXT_FIC_           "mml" // Mail Meta Language
#define EXT_FIC_           "mmm" // Movie (RIFF RMMP format) (MacroMind Director 3.x)
#define EXT_FIC_           "mmo" // Memo writer file (RapidFile)
#define EXT_FIC_           "mmp" // Output video format from Bravado board
#define EXT_FIC_           "mmx" // Command & Conquer Red Alert 2 Map file

#define EXT_FIC_           "mmz" // MusicMatch Theme file
#define EXT_FIC_           "mnd" // Menu source (AutoCAD Menu Compiler)
#define EXT_FIC_           "mng" // Map (DeLorme Map'n'Go)
#define EXT_FIC_           "mnt" // Menu memo (FoxPro)
#define EXT_FIC_           "mnu" // Advanced macro (HP NewWave)

#define EXT_FIC_           "mnx" // Compiled menu (AutoCAD)

#define EXT_FIC_           "mny" // Account book (MS Money)
#define EXT_FIC_           "mob" // Device definition (PEN Windows)
#define EXT_FIC_           "mod" // Modula-2 source code file (Clarion Modula-2)


#define EXT_FIC_           "mol" // MDL Molfile 
#define EXT_FIC_           "mon" // Monitor description (ReadMail)
#define EXT_FIC_           "mov" // QuickTime Video Clip


#define EXT_FIC_           "mp2" // Mpeg audio file (xing)
#define EXT_FIC_           "mpa " // MPEG Audio Stream, Layer I, II or III 
#define EXT_FIC_           "mpc" // Calender file (MS Project)
#define EXT_FIC_           "mpd" // MS Project database file
#define EXT_FIC_           "mpe" // MPEG Movie Clip
#define EXT_FIC_           "mpf" // MS Design Gallery

#define EXT_FIC_           "mpg" // Mpeg animation
#define EXT_FIC_           "mpm" // Mathplan macro (WordPerfect Library)
#define EXT_FIC_           "mpp" // Project file (MS Project)

#define EXT_FIC_           "mpq" // Blizzard Game Data file
#define EXT_FIC_           "mpr" // Generated program (FoxPro)
#define EXT_FIC_           "mps" // Multimedia file

#define EXT_FIC_           "mpt" // Bitmap graphics (Multipage TIFF)

#define EXT_FIC_           "mpv" // View file (MS Project)
#define EXT_FIC_           "mpw" // MosASCII Project Workspace file
#define EXT_FIC_           "mpx" // Compiled menu program (FoxPro)
#define EXT_FIC_           "mrb" // Multiple Resolution Bitmap graphics (MS C/C++)
#define EXT_FIC_           "mrc" // MIRC Script file

#define EXT_FIC_           "mrk" // Informative Graphics markup file
#define EXT_FIC_           "mrs" // Macro Resource file (WordPerfect for Win)
#define EXT_FIC_           "msc" // MS C makefile
#define EXT_FIC_           "msf" // Multiple Sequence file
#define EXT_FIC_           "msg" // Message
#define EXT_FIC_           "msi" // Windows Installer file
#define EXT_FIC_           "mso" // Math Script Object file

#define EXT_FIC_           "msp" // Bitmap graphics (Microsoft Paint)
#define EXT_FIC_           "mspx " // XML based Web Page
#define EXT_FIC_           "mss" // Manuscript text file (Perfect Writer - Scribble - MINCE - Jove)
#define EXT_FIC_           "mst" // ChemFinder Chemical Structure Index

#define EXT_FIC_           "msv" // Sony Memory Stick Format
#define EXT_FIC_           "msw" // Text file (MS Word)
#define EXT_FIC_           "msx" // Compressed CP/M file archive created by MSX
#define EXT_FIC_           "mtd" // Digital Sheet Music
#define EXT_FIC_           "mth" // Math file (Derive)
#define EXT_FIC_           "mtm" // Multitracker Module music
#define EXT_FIC_           "mts" // Viewpoint iPix file
#define EXT_FIC_           "mtw" // Datafile (Minitab)
#define EXT_FIC_           "mtx" // Temporary File often used by a browser or TWAIN device

#define EXT_FIC_           "mu" //  Menu (Quattro Pro)
#define EXT_FIC_           "mu3" // Myriad Music file (packed sounds & digital tracks)
#define EXT_FIC_           "muf" // ProtoMuck Multi User Forth Program
#define EXT_FIC_           "mul" // Ultima Online Game
#define EXT_FIC_           "mus" // MusicTime Sound file

#define EXT_FIC_           "mvb" // Database

#define EXT_FIC_           "mvc" // Music Collector Collection Manager file
#define EXT_FIC_           "mvd " // MicroDVD (DVD movie file)
#define EXT_FIC_           "mvf" // Stop frame file (AutoCAD AutoFlix)
#define EXT_FIC_           "mvi" // Movie command file (AutoCAD AutoFlix)
#define EXT_FIC_           "mvw" // Log file (Saber LAN)
#define EXT_FIC_           "mwf" // Animation (ProMotion)
#define EXT_FIC_           "mwv" // MovieWorks file
#define EXT_FIC_           "mxd" // GIS Project file 
#define EXT_FIC_           "mxe" // Macro Express

#define EXT_FIC_           "MXF " // Material eXchange Format for the interchange of audio-visual material (associated data and metadata).
#define EXT_FIC_           "mxm" // MS Project/Outlook Team Assign Task
#define EXT_FIC_           "mxp" // Macromedia Extension Manager

#define EXT_FIC_           "mxt" // Data (MS C)
#define EXT_FIC_           "myp" // Presentation (MM Make Your Point)
#define EXT_FIC_           "myr" // Myriad Music file
#define EXT_FIC_           "mys" // Myst Saved Game
#define EXT_FIC_           "myt" // Myriad Tutorial file.m  Function (program) (Matlab)


#define EXT_FIC_           "m11" // Text file (MASS11)
#define EXT_FIC_           "m2p" // MPEG-2 Program Stream Format file
#define EXT_FIC_           "m2v" // MPEG-2 Video Only file
#define EXT_FIC_           "m3" //  Modula 3 source code file
#define EXT_FIC_           "m3d" // 3d animation macro
#define EXT_FIC_           "m3u" // Music Playlist (Winamp)
#define EXT_FIC_           "m4" //  M4 preprocessor file (unix)
#define EXT_FIC_           "m_u" // Backup of boot sector, FAT and boot dir (MazeGold)
#define EXT_FIC_           "ma3" // Macro (Harvard Graphics 3.0)
#define EXT_FIC_           "mac" // Bitmap graphics (Macintosh MacPaint)

#define EXT_FIC_           "mad" // MS Access Module Shortcut
#define EXT_FIC_           "mag" // Woody Lynn's MAG graphics format (MPS Magro Paint System)
#define EXT_FIC_           "mai" // Mail (VAX)
#define EXT_FIC_           "mak" // Makefile

#define EXT_FIC_           "man" // Command manual
#define EXT_FIC_           "map" // Color palette

#define EXT_FIC_           "mar" // Assembly program (VAX Macro)
#define EXT_FIC_           "mas" // Smartmaster set (Freelance Graphics)
#define EXT_FIC_           "mat" // Data file (Matlab)
#define EXT_FIC_           "max" // Max source code file

#define EXT_FIC_           "mb" //  Memo field values for database (Paradox)
#define EXT_FIC_           "mbf" // MS Money Backup file
#define EXT_FIC_           "mbk" // Multiple index file backup (dBASE IV)
#define EXT_FIC_           "mbx" // Mailbox (Eudora/Zerberus)
#define EXT_FIC_           "mcc" // Configuration file (Mathcad)
#define EXT_FIC_           "mcd" // Document (Mathcad)
#define EXT_FIC_           "mcf" // Mathcad font

#define EXT_FIC_           "mci" // Mci command script (Media Control Interface)
#define EXT_FIC_           "mcp" // Application script (Capsule)

#define EXT_FIC_           "mcr" // DataCAD Keyboard macro file
#define EXT_FIC_           "mcw" // Text file (MacWrite II)
#define EXT_FIC_           "mcx" // Graphic file
#define EXT_FIC_           "md" //  Compressed file archive created by MDCD (mdcd10.arc)
#define EXT_FIC_           "md5" // Message Digest 5 (Easy MD5 Creator)
#define EXT_FIC_           "mda" // Data (MS Access)
#define EXT_FIC_           "mdb" // Database (MS Access)
#define EXT_FIC_           "mdf" // Accelio Capture Classic (JetForm) Filler

#define EXT_FIC_           "mdl" // Model (3D Design Plus)

#define EXT_FIC_           "mdm" // Modem definition (TELIX)
#define EXT_FIC_           "mdr" // FaxTalk Modem Doctor Modem Report file
#define EXT_FIC_           "mdt" // Data table (MS ILink incremental linker)
#define EXT_FIC_           "mdx" // Multiple index file (dBASE IV)
#define EXT_FIC_           "mdz" // MS Access Wizard Template
#define EXT_FIC_           "me" //  Usually ASCII text file READ.ME
#define EXT_FIC_           "meb" // Macro Editor bottom overflow file (WordPerfect Library)
#define EXT_FIC_           "med" // Macro Editor delete save (WordPerfect Library)

#define EXT_FIC_           "mem" // Macro Editor macro (WordPerfect Library)

#define EXT_FIC_           "meq" // Macro Editor print queue file (WordPerfect Library)
#define EXT_FIC_           "mer" // Macro Editor resident area (WordPerfect Library) (vakioalue)
#define EXT_FIC_           "mes" // Macro Editor work space file (WordPerfect Library)

#define EXT_FIC_           "met" // Document (Omnipage Pro)

#define EXT_FIC_           "meu" // Menu group (DOS Shell)
#define EXT_FIC_           "mex" // Mex file (executable command) (Matlab)


#define EXT_FIC_           "mf" //  Metafont text file
#define EXT_FIC_           "mgf" // Font (Micrografx)
#define EXT_FIC_           "mhp" // MS Home Publishing Project
#define EXT_FIC_           "mht  " // MS MHTML Document
#define EXT_FIC_           "mib" // Snmp MIB file
#define EXT_FIC_           "mic" // Microsoft Image Composer file
#define EXT_FIC_           "mid" // Standard MIDI file (music synthetizers)
#define EXT_FIC_           "mif" // Maker Interchange Format (FrameMaker)
#define EXT_FIC_           "mii" // Datafile (MicroStat-II)
#define EXT_FIC_           "mim" // MIME file
#define EXT_FIC_           "mio" // Multimedia Interactive Object
#define EXT_FIC_           "mip" // Paint Shop Pro Multiple Image Print file
#define EXT_FIC_           "mis" // Delta Force Land Warrior Mission


#define EXT_FIC_           "mix" // Object file (Power C)
#define EXT_FIC_           "mk" //  Makefile
#define EXT_FIC_           "mke" // Makefile (MS Windows SDK)
#define EXT_FIC_           "mki" // Japanese graphics MAKIchan format (MagView 0.5)
#define EXT_FIC_           "mks" // Data (TACT)
#define EXT_FIC_           "ml3" // Project (Milestones 3.x)
#define EXT_FIC_           "mlb" // Macro library file (Symphony)
#define EXT_FIC_           "mlm" // Novel Groupwise e-mail file
#define EXT_FIC_           "mm" //  Text file (MultiMate Advantage II)
#define EXT_FIC_           "mmc" // Media Catalog  

#define EXT_FIC_           "mmd" // Peristudio/PeriProducer file
#define EXT_FIC_           "mmf" // Mail message file (MS Mail)
#define EXT_FIC_           "mml" // Mail Meta Language
#define EXT_FIC_           "mmm" // Movie (RIFF RMMP format) (MacroMind Director 3.x)
#define EXT_FIC_           "mmo" // Memo writer file (RapidFile)
#define EXT_FIC_           "mmp" // Output video format from Bravado board
#define EXT_FIC_           "mmx" // Command & Conquer Red Alert 2 Map file

#define EXT_FIC_           "mmz" // MusicMatch Theme file
#define EXT_FIC_           "mnd" // Menu source (AutoCAD Menu Compiler)
#define EXT_FIC_           "mng" // Map (DeLorme Map'n'Go)
#define EXT_FIC_           "mnt" // Menu memo (FoxPro)
#define EXT_FIC_           "mnu" // Advanced macro (HP NewWave)

#define EXT_FIC_           "mnx" // Compiled menu (AutoCAD)

#define EXT_FIC_           "mny" // Account book (MS Money)
#define EXT_FIC_           "mob" // Device definition (PEN Windows)
#define EXT_FIC_           "mod" // Modula-2 source code file (Clarion Modula-2)


#define EXT_FIC_           "mol" // MDL Molfile 
#define EXT_FIC_           "mon" // Monitor description (ReadMail)
#define EXT_FIC_           "mov" // QuickTime Video Clip


#define EXT_FIC_           "mp2" // Mpeg audio file (xing)
#define EXT_FIC_           "mp3" // mp3PRO Audio file



#define EXT_FIC_           "mp4" // MPEG-4 Video File 
#define EXT_FIC_           "mpc" // Calender file (MS Project)
#define EXT_FIC_           "mpd" // MS Project database file
#define EXT_FIC_           "mpe" // MPEG Movie Clip
#define EXT_FIC_           "mpf" // MS Design Gallery

#define EXT_FIC_           "mpg" // Mpeg animation
#define EXT_FIC_           "mpm" // Mathplan macro (WordPerfect Library)
#define EXT_FIC_           "mpp" // Project file (MS Project)

#define EXT_FIC_           "mpq" // Blizzard Game Data file
#define EXT_FIC_           "mpr" // Generated program (FoxPro)
#define EXT_FIC_           "mps" // Multimedia File

#define EXT_FIC_           "mpt" // Bitmap graphics (Multipage TIFF)

#define EXT_FIC_           "mpv" // View file (MS Project)
#define EXT_FIC_           "mpw" // MosASCII Project Workspace file
#define EXT_FIC_           "mpx" // Compiled menu program (FoxPro)
#define EXT_FIC_           "mrb" // Multiple Resolution Bitmap graphics (MS C/C++)
#define EXT_FIC_           "mrc" // MIRC Script file

#define EXT_FIC_           "mrk" // Informative Graphics markup file
#define EXT_FIC_           "mrs" // Macro Resource file (WordPerfect for Win)
#define EXT_FIC_           "msc" // MS C makefile
#define EXT_FIC_           "msd" // MS Diagnostic Utility Report
#define EXT_FIC_           "msf" // Multiple Sequence file
#define EXT_FIC_           "msg" // Message
#define EXT_FIC_           "msi" // Windows Installer file
#define EXT_FIC_           "msm" // MultiSIM Circuit Diagram
#define EXT_FIC_           "mso" // Math Script Object file


#define EXT_FIC_           "msp" // Bitmap graphics (Microsoft Paint)
#define EXT_FIC_           "mspx" // XML based Web Page.mssManuscript text file (Perfect Writer - Scribble - MINCE - Jove)
#define EXT_FIC_           "mst" // ChemFinder Chemical Structure Index

#define EXT_FIC_           "msv" // Sony Memory Stick Format
#define EXT_FIC_           "msw" // Text file (MS Word)
#define EXT_FIC_           "msx" // Compressed CP/M file archive created by MSX
#define EXT_FIC_           "mtd" // Digital Sheet Music
#define EXT_FIC_           "mth" // Math file (Derive)
#define EXT_FIC_           "mtm" // Multitracker Module music
#define EXT_FIC_           "mts" // Viewpoint iPix file
#define EXT_FIC_           "mtw" // Datafile (Minitab)
#define EXT_FIC_           "mtx" // Temporary File often used by a browser or TWAIN device

#define EXT_FIC_           "mu" //  Menu (Quattro Pro)
#define EXT_FIC_           "mu3" // Myriad Music file (packed sounds & digital tracks)
#define EXT_FIC_           "muf" // ProtoMuck Multi User Forth Program
#define EXT_FIC_           "mul" // Ultima Online Game
#define EXT_FIC_           "mus" // MusicTime Sound file

#define EXT_FIC_           "mvb" // Database

#define EXT_FIC_           "mvc" // Music Collector Collection Manager file
#define EXT_FIC_           "mvd" // MicroDVD (DVD movie  file).mvfStop frame file (AutoCAD AutoFlix)
#define EXT_FIC_           "mvi" // Movie command file (AutoCAD AutoFlix)
#define EXT_FIC_           "mvw" // Log file (Saber LAN)
#define EXT_FIC_           "mwf" // Animation (ProMotion)
#define EXT_FIC_           "mwp" // Lotus Wordpro 97 Smartmaster file

#define EXT_FIC_           "mwv" // MovieWorks file
#define EXT_FIC_           "mxd" // GIS Project file
#define EXT_FIC_           "mxe" // Macro Express

#define EXT_FIC_           "mxf" // Material eXchange Format.mxmMS Project/Outlook Team Assign Task
#define EXT_FIC_           "mxp" // Macromedia Extension Manager

#define EXT_FIC_           "mxt" // Data (MS C)
#define EXT_FIC_           "myp" // Presentation (MM Make Your Point)
#define EXT_FIC_           "myr" // Myriad Music file
#define EXT_FIC_           "mys" // Myst Saved Game
#define EXT_FIC_           "myt" // Myriad Tutorial file
#define EXT_FIC_           "na2" // Netscape Mail file
#define EXT_FIC_           "nam" // MS Office Name file 
#define EXT_FIC_           "nap" // Naplps file (VideoShow) (EnerGraphics)
#define EXT_FIC_           "nav" // MSN Application Extension
#define EXT_FIC_           "nb" //  Text file (Nota Bene)
#define EXT_FIC_           "nc" //  Graphics (netcdf)

#define EXT_FIC_           "ncb" // MS Developer Studio file
#define EXT_FIC_           "ncc" // Cnc (Computer Numeric Control) control file (CamView 3D)
#define EXT_FIC_           "ncd" // CoverDesigner  


#define EXT_FIC_           "ncf" // Lotus Notes Internal Clipboard

#define EXT_FIC_           "nch" // Outlook Express folder file

#define EXT_FIC_           "ndb" // Network database (Intellicom - Compex)
#define EXT_FIC_           "nde " // Video format - various manufactures of surveillance camera systems
#define EXT_FIC_           "ndx" // Index file (dBASE II - III - IV - dBFast)
#define EXT_FIC_           "neb" // Nortec H.E.L.P.
#define EXT_FIC_           "ned" // MSN Application Extension
#define EXT_FIC_           "neo" // Raster graphics (Atari Neochrome)
#define EXT_FIC_           "nes" // Nintendo Entertainment System ROM Image
#define EXT_FIC_           "net" // Network configuration/info file
#define EXT_FIC_           "new" // New info
#define EXT_FIC_           "nfo" // Info file
#define EXT_FIC_           "ng" //  Online documentation database (Norton Guide)
#define EXT_FIC_           "ngf" // Enterasys Networks NetSight generated format file
#define EXT_FIC_           "ngg" // Nokia Group Graphics
#define EXT_FIC_           "nif" // NetImmerse File Format
#define EXT_FIC_           "nlm" // Netware Loadable Module
#define EXT_FIC_           "nls" // Code Page National Language Support
#define EXT_FIC_           "nlx" // Form (FormWorx 3.0)
#define EXT_FIC_           "nmd" // SwordSearcher file
#define EXT_FIC_           "nmi" // SwordSearcher file
#define EXT_FIC_           "nmo" // Virtools Behavioral Objects
#define EXT_FIC_           "nms" // Numega Softice's Loader file

#define EXT_FIC_           "nnb" // newnovelist Story Outline
#define EXT_FIC_           "nob" // VersaPro Word Exchange file
#define EXT_FIC_           "nol" // Nokia Operator Logo
#define EXT_FIC_           "not" // Acrobat Spelling file

#define EXT_FIC_           "now" // Text file 
#define EXT_FIC_           "np" //  Project schedule (Nokia Planner) (Visual Planner 3.x)
#define EXT_FIC_           "npa" // ReliaSoft Weibull++ 6 
#define EXT_FIC_           "npi" // Source for DGEN.EXE intepreter (dBASE Application Generator)
#define EXT_FIC_           "nra" // Nero Audio-CD Compilation
#define EXT_FIC_           "nrb" // Nero CD-ROM Boot Compilation
#define EXT_FIC_           "nrg" // Norton Registration Entries


#define EXT_FIC_           "nri" // Nero ISO CD-ROM compilation
#define EXT_FIC_           "nrl" // iManage file
#define EXT_FIC_           "nsc" // Noder file (Polish)

#define EXT_FIC_           "nsf" // Lotus Notes / Domino database
#define EXT_FIC_           "nsi" // Nullsoft Install System Script
#define EXT_FIC_           "nst" // Music (NoiseTracker)
#define EXT_FIC_           "nt" //  Startup files (Windows NT)
#define EXT_FIC_           "ntf" // Lotus Notes / Domino template file
#define EXT_FIC_           "ntp" // Neato CD Labels
#define EXT_FIC_           "ntr" // Executable ASCII text file (strip header and rename) (netrun31.zip)
#define EXT_FIC_           "nts" // Tutorial (Norton)

#define EXT_FIC_           "ntx" // Index (Clipper 5)
#define EXT_FIC_           "ntz" // InVircible Directory Integrity Information
#define EXT_FIC_           "nuf" // Message for new users on their 1st call (Procomm Plus)
#define EXT_FIC_           "nwc" // Noteworthy Composer song file
#define EXT_FIC_           "nws" // Info text file (latest news) (ASCII)
#define EXT_FIC_           "nxt" // Sound (NeXT format)
#define EXT_FIC_           "o" //   Object file (unix - Atari - GCC)
#define EXT_FIC_           "o$$" // Outfile (Sprint)
#define EXT_FIC_           "oaz" // Fax (NetFax Manager)
#define EXT_FIC_           "ob" //  Object cut/paste file (IBM LinkWay)
#define EXT_FIC_           "obd" // MS Office Binder
#define EXT_FIC_           "obj" // Object code (Intel Recolatable Object Module)
#define EXT_FIC_           "obr" // Object browser data file (Borland C++)
#define EXT_FIC_           "obs" // Script (ObjectScript)
#define EXT_FIC_           "obv" // Visual interface (ObjectScript)
#define EXT_FIC_           "oca" // Control Typelib Cache
#define EXT_FIC_           "ocf" // Object Craft File (Object Craft)
#define EXT_FIC_           "ocm" // AOL Advertising Control files

#define EXT_FIC_           "ocp" // Advanced Art Studio

#define EXT_FIC_           "ocr" // Incoming fax transcribed to text (FAXGrapper)
#define EXT_FIC_           "oct" // Radiance Octree Format
#define EXT_FIC_           "ocx" // OLE custom control
#define EXT_FIC_           "odf" // Open Document Interchange


#define EXT_FIC_           "odl" // Type library source (Visual C++)
#define EXT_FIC_           "oeb" // Outlook Express Backup Wizard
#define EXT_FIC_           "ofc" // Open Financial Connectivity file
#define EXT_FIC_           "ofd" // Form definition (ObjectView)
#define EXT_FIC_           "off" // Object File Format vector graphics
#define EXT_FIC_           "ofm" // Adobe font
#define EXT_FIC_           "oft" // MS Outlook Item Template
#define EXT_FIC_           "ofx" // Olicom Fax 

#define EXT_FIC_           "ogg" // Ogg Vorbis Codec Compressed WAV file
#define EXT_FIC_           "ogm" // Ogg Vorbis Compressed Video file
#define EXT_FIC_           "okt" // Music (Oktalizer)
#define EXT_FIC_           "olb" // Object library (VAX)
#define EXT_FIC_           "old" // Backup file
#define EXT_FIC_           "ole" // Object Linking and Embedding Object .oliText file (Olivetti)
#define EXT_FIC_           "omg" // OpenMG Jukebox
#define EXT_FIC_           "oms" // Briggs Softworks Order Maven


#define EXT_FIC_           "ond" // Lotus Notes-related file
#define EXT_FIC_           "oom" // Swap file (Shroom)
#define EXT_FIC_           "opd" // Omnipage file
#define EXT_FIC_           "opf" // Flip Album file
#define EXT_FIC_           "opl" // Psion Organiser Programming Language Source file
#define EXT_FIC_           "opn" // Active options (Exact)
#define EXT_FIC_           "opt" // Optimize support file (QEMM)
#define EXT_FIC_           "opw" // Organization chart (Org Plus for Windows)
#define EXT_FIC_           "opx" // Inactive options (Exact)
#define EXT_FIC_           "or2" // Lotus Organizer 2 file
#define EXT_FIC_           "or3" // Lotus Organizer 97 file
#define EXT_FIC_           "or4" // Lotus Organizer file
#define EXT_FIC_           "or5" // Lotus Organizer file
#define EXT_FIC_           "ora" // Parameter file (Oracle)
#define EXT_FIC_           "org" // Calendar file (Lotus Organizer)
#define EXT_FIC_           "osd" // Open Software Description file
#define EXT_FIC_           "oss" // MS Office Saved Search
#define EXT_FIC_           "ost" // Microsoft Outlook Offline file
#define EXT_FIC_           "otf" // Open Type Format
#define EXT_FIC_           "otl" // Outline font description (Z-Soft Type Foundry)
#define EXT_FIC_           "otx" // Text file (Olivetti Olitext Plus)
#define EXT_FIC_           "out" // Output file
#define EXT_FIC_           "ov1" // Overlay file (part of program to be loaded when needed)
#define EXT_FIC_           "ov2" // Overlay file (part of program to be loaded when needed)
#define EXT_FIC_           "ovd" // Datafile (ObjectVision)
#define EXT_FIC_           "ovl" // Overlay file (part of program to be loaded when needed)
#define EXT_FIC_           "ovr" // Overlay file (part of program to be loaded when needed)
#define EXT_FIC_           "ovw" // Cool Edit Pro Overviewfile


#define EXT_FIC_           "ows" // Web Studio 2 Project file
#define EXT_FIC_           "p" //   Pascal source code file


#define EXT_FIC_           "p16" // Music (16 channels) (ProTracker Studio 16)
#define EXT_FIC_           "p22" // Patch file (Patch22)
#define EXT_FIC_           "p65" // Adobe Pagemaker v6.5
#define EXT_FIC_           "p7m" // PKCS #7 MIME Message
#define EXT_FIC_           "pa" // Print Artist
#define EXT_FIC_           "pa1" // Worktable (PageAhead)
#define EXT_FIC_           "pab" // Microsoft Outlook personal address book
#define EXT_FIC_           "pac" // Stad Image (graphics ?)

#define EXT_FIC_           "pad" // Keypad definition (Telemate)
#define EXT_FIC_           "paf" // PARIS audio format

#define EXT_FIC_           "pak" // Compressed file archive created by PAK (pak251.exe)
#define EXT_FIC_           "pal" // Adobe Pagemaker Library Palette



#define EXT_FIC_           "pan" // Printer-specific file (copy to coreldrw.ink) (CorelDRAW)
#define EXT_FIC_           "par" // Parts application (Digitalk PARTS)


#define EXT_FIC_           "pas" // Pascal source code file
#define EXT_FIC_           "pat" // Hatch patterns (AutoCAD - Photostyler)

#define EXT_FIC_           "pb" //  Fax (FAXability Plus)


#define EXT_FIC_           "pb1" // Document (First Publisher for Windows)
#define EXT_FIC_           "pba" // Powerbasic BASIC source code (Genus)
#define EXT_FIC_           "pbd" // Phone book (FaxNOW! - Faxit)
#define EXT_FIC_           "pbf" // Turtle Beach Pinnacle Bank file

#define EXT_FIC_           "pbi" // Powerbasic include file (Genus)

#define EXT_FIC_           "pbk " // Microsoft XP Remote Access Phonebook file
#define EXT_FIC_           "pbl" // Powerbasic library (Genus)
#define EXT_FIC_           "pbm" // Pbm Portable Bit Map graphics

#define EXT_FIC_           "pbo" // Profiler Binary Output (MS Source Profiler)
#define EXT_FIC_           "pbr" // Microsoft Publisher backup file.pbtProfiler Binary Table (MS Source Profiler)
#define EXT_FIC_           "pc" //  Text file containing IBM PC specific info
#define EXT_FIC_           "pc3" // Custom palette (Harvard Graphics 3.0)
#define EXT_FIC_           "pc8" // Ascii text IBM8 character set (NewWave Write)
#define EXT_FIC_           "pcb" // Broderbund Print Shop Business Card

#define EXT_FIC_           "pcc" // Cutout picture vector graphics (PC Paintbrush)
#define EXT_FIC_           "pcd" // Graphics (Kodak PhotoCD)
#define EXT_FIC_           "pcf" // Profiler Command File (MS Source Profiler)
#define EXT_FIC_           "pch" // Patch file

#define EXT_FIC_           "pcj" // Multimedia authoring tool graphics (IBM's Linkaway-Live)
#define EXT_FIC_           "pck" // Pickfile (Turbo Pascal)
#define EXT_FIC_           "pcl" // HP-PCL graphics data (HP Printer Control Language)
#define EXT_FIC_           "pcm" // Plasmacam CAD/CAM system file
#define EXT_FIC_           "pcs" // PICS Animation
#define EXT_FIC_           "pct" // Bitmap Graphic 
#define EXT_FIC_           "pcw" // Text file (PC Write)
#define EXT_FIC_           "pcx" // Bitmap graphics (PC Paintbrush)
#define EXT_FIC_           "pda" // Bitmap graphics
#define EXT_FIC_           "pdb" // Data (TACT)
#define EXT_FIC_           "pdc " // Personal Database Creator file
#define EXT_FIC_           "pdd" // Adobe PhotoDeluxe Image
#define EXT_FIC_           "pde " // Principalm Data Extract files

#define EXT_FIC_           "pdf" // Adobe Portable Document Format


#define EXT_FIC_           "pdg" // Printshop Deluxe files
#define EXT_FIC_           "pdl" // Project Description Language file (Borland C++ 4.5)
#define EXT_FIC_           "pdr" // Port or printer driver
#define EXT_FIC_           "pds" // Incredimail

#define EXT_FIC_           "pdt" // ProCite Primary Database

#define EXT_FIC_           "pdv" // Printer driver (Paintbrush)
#define EXT_FIC_           "pdw" // Document (Professional Draw)
#define EXT_FIC_           "pe4" // Photo Explorer Thumbnail
#define EXT_FIC_           "peb" // Program Editor bottom overflow file (WordPerfect Library)
#define EXT_FIC_           "ped" // Program Editor delete save (WordPerfect Library)
#define EXT_FIC_           "pem" // Program Editor macro (WordPerfect Library)
#define EXT_FIC_           "peq" // Program Editor print queue file (WordPerfect Library)
#define EXT_FIC_           "per" // Program Editor resident area (WordPerfect Library) (vakioalue)
#define EXT_FIC_           "pes" // Program Editor work space file (WordPerfect Library)
#define EXT_FIC_           "pet" // Program Editor top overflow file (WordPerfect Library)
#define EXT_FIC_           "pf" // Monitor/printer profile file
#define EXT_FIC_           "pfa" // Type 3 font file (unhinted PostScript font)
#define EXT_FIC_           "pfb" // Type 1 font file
#define EXT_FIC_           "pfc" // Text file (First Choice)
#define EXT_FIC_           "pfg" // jEEPers file
#define EXT_FIC_           "pfk" // Programmable function keys (XTreePro)
#define EXT_FIC_           "pfm" // Windows Type 1 font metric file
#define EXT_FIC_           "pfs" // Database (PFS:FILE) - text file (PFS:Write)
#define EXT_FIC_           "pft" // Printer font (ChiWriter)
#define EXT_FIC_           "pg" //  Page cut/paste file (IBM LinkWay)
#define EXT_FIC_           "pgi" // Printer Graphics File device driver (PGRAPH library)
#define EXT_FIC_           "pgm" // Portable Grayscale bitMap graphics

#define EXT_FIC_           "pgp" // Support file (Pretty Good Privacy RSA System)
#define EXT_FIC_           "pgs" // Manual page (man4dos)
#define EXT_FIC_           "ph" //  Optimized .goh file (Geoworks)


#define EXT_FIC_           "phb" // NewLeaf PhraseBook



#define EXT_FIC_           "phn" // Phone list (UltraFax - QmodemPro)
#define EXT_FIC_           "php" // MS Picture It! Publishing Project File


#define EXT_FIC_           "pho" // Phone database (Metz Phone for Windows)
#define EXT_FIC_           "phr" // Phrases (LocoScript)
#define EXT_FIC_           "pic" // Pixar picture file (SDSC Image Tool)


#define EXT_FIC_           "pif" // Program Information File (Windows 3.x)

#define EXT_FIC_           "pip" // Personalized menu and toolbar (MS Office)
#define EXT_FIC_           "pit" // Compressed Mac file archive created by PACKIT (unpackit.zoo)
#define EXT_FIC_           "pix" // Alias image file (SDSC Image Tool)
#define EXT_FIC_           "pj64" // Project 64 game files.mswmm  Windows Movie Maker Project file.pj Project (CA-SuperProject)
#define EXT_FIC_           "pjt" // Project memo (FoxPro)
#define EXT_FIC_           "pjx" // Project (FoxPro)
#define EXT_FIC_           "pk" //  Packed bitmap font bitmap file (TeX DVI drivers)
#define EXT_FIC_           "pk3" // American McGee Alice Archive



#define EXT_FIC_           "pka" // Compressed file archive created by PKARC
#define EXT_FIC_           "pkd" // Top Secret Crypto Gold file
#define EXT_FIC_           "pkg" // Installer script (Next)
#define EXT_FIC_           "pkt" // Fidonet packet
#define EXT_FIC_           "pl" //  Perl source code file



#define EXT_FIC_           "pl1" // Room plan (3D Home Architect)
#define EXT_FIC_           "pl3" // Chart palette (Harvard Graphics 3.0)
#define EXT_FIC_           "plb" // Library (FoxPro)
#define EXT_FIC_           "plc" // Add-in file (functions - macros - applications) (Lotus 1-2-3)
#define EXT_FIC_           "pll" // Pre-linked library (Clipper 5)
#define EXT_FIC_           "pln" // Spreadsheet (WordPerfect for Win)
#define EXT_FIC_           "plr" // Descent Pilot file

#define EXT_FIC_           "pls" // DisorderTracker2 Sample



#define EXT_FIC_           "plt" // AutoCAD HPGL Vector Graphic Plotter file
#define EXT_FIC_           "ply" // Data (PopMail)

#define EXT_FIC_           "pm" //  Bitmap graphics (Presentation Manager)
#define EXT_FIC_           "pm3" // Document (PageMaker 3)
#define EXT_FIC_           "pm4" // Document (PageMaker 4)
#define EXT_FIC_           "pm5" // Document (PageMaker 5)
#define EXT_FIC_           "pm6" // Document (Pagemaker 6)
#define EXT_FIC_           "pmc" // Graphics (A4TECH Scanner)
#define EXT_FIC_           "pmd" // Pagemaker file
#define EXT_FIC_           "pme" // Plazmic Media Engine file
#define EXT_FIC_           "pmf" // ArcReader GIS Mapping file
#define EXT_FIC_           "pmm" // Program file (Amaris BTX/2)
#define EXT_FIC_           "pmo" // Print Master Gold Text
#define EXT_FIC_           "pmx" // Pegasus Mail file
#define EXT_FIC_           "pn3" // Printer device driver (Harvard Graphics 3.0)
#define EXT_FIC_           "pnf" // Precompiled Setup Information (Temporary file seen during installs)
#define EXT_FIC_           "png" // Bitmap graphics (Portable Network Graphics)
#define EXT_FIC_           "pnm" // Pbm Portable aNy Map (PNM) graphics
#define EXT_FIC_           "pnt" // Macintosh painting

#define EXT_FIC_           "poh" // Optimized .goh file (Geoworks)
#define EXT_FIC_           "pop" // Messages index (PopMail)

#define EXT_FIC_           "pos" // ProCite Output Styles

#define EXT_FIC_           "pot" // PowerPoint template
#define EXT_FIC_           "pov" // Raytraced scene description file (Persistence Of Vision)
#define EXT_FIC_           "pow" // Chord chart (PowerChords)
#define EXT_FIC_           "pp" //  Compressed Amiga file archive created by POWERPACKER
#define EXT_FIC_           "ppa" // PowerPoint Add-in
#define EXT_FIC_           "ppb" // Button bar for Print Preview (WordPerfect for Win)
#define EXT_FIC_           "ppd" // PostScript Printer Description (Acrobat)
#define EXT_FIC_           "ppf" // Turtle Beach Pinnacle Program file
#define EXT_FIC_           "ppg" // MS PowerPoint Ppresentation

#define EXT_FIC_           "ppl" // Polaroidpaletteplus ColorKey device driver (Harvard Graphics 3.0)
#define EXT_FIC_           "ppm" // Portable Pixel Map graphics
#define EXT_FIC_           "ppo" // Pre-processor output (Clipper 5)
#define EXT_FIC_           "ppp" // Publication (PagePlus)
#define EXT_FIC_           "pps" // PowerPoint Slideshow

#define EXT_FIC_           "ppt" // General file extension (PowerPoint)
#define EXT_FIC_           "ppz" // PowerPoint Packaged Presentation
#define EXT_FIC_           "pqa" // Palm Query Application File (database for wireless access)
#define EXT_FIC_           "pqi" // Power Quest Drive imaging
#define EXT_FIC_           "pr2" // Presentation (Aldus Persuasion 2.x)
#define EXT_FIC_           "pr2" // Printer driver (dBASE IV)
#define EXT_FIC_           "pr3" // Postscript printer driver (dBASE IV)

#define EXT_FIC_           "prc" // Palmpilot resource file

#define EXT_FIC_           "prd" // Printer driver (many)
#define EXT_FIC_           "pre" // Presentation (Freelance Graphics)

#define EXT_FIC_           "prf" // Pixel Run Format graphics (Improces - Fastgraph)


#define EXT_FIC_           "prg" // Program (Atari)

#define EXT_FIC_           "pri" // Printer definitions (LocoScript)
#define EXT_FIC_           "prj" // Project
#define EXT_FIC_           "prm" // Parameters

#define EXT_FIC_           "prn" // DataCAD Windows Printer file
#define EXT_FIC_           "pro" // Prolog source code file

#define EXT_FIC_           "prs" // Printer Resource eg. fonts (WordPerfect for Win)


#define EXT_FIC_           "prt" // CADKEY Part file
#define EXT_FIC_           "prx" // Compiled program (FoxPro)
#define EXT_FIC_           "prz" // Freelance Graphics 97 file
#define EXT_FIC_           "ps" //  Postscript file (text/graphics) (ASCII)
#define EXT_FIC_           "psb" // Pinnacle Sound Bank

#define EXT_FIC_           "psd" // Graphics (Photoshop 3.0)

#define EXT_FIC_           "pse" // Bitmap graphics (IBM printer Page SEgment)
#define EXT_FIC_           "psf" // Outline PostScript printer font (ChiWriter)

#define EXT_FIC_           "psi" // PSION A-law Audio
#define EXT_FIC_           "psm" // Music (MASI - ProTracker)


#define EXT_FIC_           "psmdoc" // PrintShop Mail
#define EXT_FIC_           "psp" // PaintShop Pro Image


#define EXT_FIC_           "psr" // Project Scheduler Resource file
#define EXT_FIC_           "pst" // MS Outlook personal folder
#define EXT_FIC_           "psw" // WinXP Backup Password File
#define EXT_FIC_           "pt3" // Device driver (Harvard Graphics 3.0)

#define EXT_FIC_           "pt4" // Template (PageMaker 4)
#define EXT_FIC_           "ptb" // Script (PubTech BatchWorks)
#define EXT_FIC_           "ptm" // Macro (PubTech BatchWorks)
#define EXT_FIC_           "ptn" // PaperPort Thumbnail Images
#define EXT_FIC_           "ptp" // Act! Modem Sync file
#define EXT_FIC_           "ptr" // Qwk reader pointer file (QMail)
#define EXT_FIC_           "pts" // Infinity Engine Game Tileset

#define EXT_FIC_           "ptx" // Real Legal E-Transcript 
#define EXT_FIC_           "pub" // Page template (MS Publisher)


#define EXT_FIC_           "put" // Compressed file archive created by PUT (put334.zip)
#define EXT_FIC_           "puz" // Across Lite Crossword Puzzle

#define EXT_FIC_           "pva" // Hauppauge DVB-Software
#define EXT_FIC_           "pvd" // Script (Instalit)
#define EXT_FIC_           "pvl" // Library (Instalit)
#define EXT_FIC_           "pvt" // Local Fidonet pointlist
#define EXT_FIC_           "pw" //  Text file (Professional Write)
#define EXT_FIC_           "pwd" // Pocket Word document

#define EXT_FIC_           "pwl" // Password List
#define EXT_FIC_           "pwp" // Text document (Professional WritePlus)
#define EXT_FIC_           "pwz" // MS Powerpoint Wizard
#define EXT_FIC_           "px" //  Primary database index (Paradox)
#define EXT_FIC_           "pxl" // Pocket Excel Spreadsheet
#define EXT_FIC_           "py" //  Python script file
#define EXT_FIC_           "pyc" // Compiled PYTHON script file
#define EXT_FIC_           "pyd" // Binary Python Extension on Windows
#define EXT_FIC_           "pyw" // Python GUI Script on Windows
#define EXT_FIC_           "pz2" // Curious Labs Poser Pose file
#define EXT_FIC_           "pz3" // Curious Labs Poser Document
#define EXT_FIC_           "pza" // MGI PhotoSuite II/III/4 Album file
#define EXT_FIC_           "pzd" // Default settings (Pizazz Plus)
#define EXT_FIC_           "pzl" // Jigs@w Puzzle


#define EXT_FIC_           "pzo" // Overlay file (Pizazz Plus)
#define EXT_FIC_           "pzp" // MGI PhotoSuite II/III/4 Project file

#define EXT_FIC_           "pzs" // Settings (Pizazz Plus)
#define EXT_FIC_           "pzt" // Transfer file (Pizazz Plus)
#define EXT_FIC_           "pzx" // Swap file (Pizazz Plus)
#define EXT_FIC_           "q9q" // BladePro Graphic Plugin file
#define EXT_FIC_           "qad" // QuickArt database
#define EXT_FIC_           "qag" // Quick Access Group (Norton Desktop)
#define EXT_FIC_           "qap" // Application (Omnis Quartz)
#define EXT_FIC_           "qbb" // QuickBooks for Windows Backup file
#define EXT_FIC_           "qbe" // Saved query (Query By Example) (dBASE IV - Quattro Pro)
#define EXT_FIC_           "qbl" // Business Lawyer Document
#define EXT_FIC_           "qbo" // Compiled query (dBASE IV)
#define EXT_FIC_           "qbr" // QuickBooks Report
#define EXT_FIC_           "qbw" // Spreadsheet (QuickBooks for Windows)
#define EXT_FIC_           "qcn" // Qualcomm Phonebook file
#define EXT_FIC_           "qcp" // Qualcomm PureVoice File

#define EXT_FIC_           "qd0" // Data file - segment 10 (Omnis Quartz)
#define EXT_FIC_           "qd1" // Data file - segment 1 (Omnis Quartz)
#define EXT_FIC_           "qd2" // Data file - segment 2 (Omnis Quartz)
#define EXT_FIC_           "qd3" // Data file - segment 3 (Omnis Quartz)
#define EXT_FIC_           "qd4" // Data file - segment 4 (Omnis Quartz)
#define EXT_FIC_           "qd5" // Data file - segment 5 (Omnis Quartz)
#define EXT_FIC_           "qd6" // Data file - segment 6 (Omnis Quartz)
#define EXT_FIC_           "qd7" // Data file - segment 7 (Omnis Quartz)
#define EXT_FIC_           "qd8" // Data file - segment 8 (Omnis Quartz)
#define EXT_FIC_           "qd9" // Data file - segment 9 (Omnis Quartz)
#define EXT_FIC_           "qdat" // Quicktime Installer Cache
#define EXT_FIC_           "qdb" // Quicken data file
#define EXT_FIC_           "qdf" // Quicken for Windows data file
#define EXT_FIC_           "qdt" // Quark Xpress Dictionary file



#define EXT_FIC_           "qdv" // Graphics (Steve Blackstock Giffer)
#define EXT_FIC_           "qe4" // Kingpin Project file
#define EXT_FIC_           "qef" // Query file (Q+E for MS Excel)
#define EXT_FIC_           "qel" // Quicken Electronic Library file
#define EXT_FIC_           "qfl" // Quicken Family Lawyer file
#define EXT_FIC_           "qfx" // Fax (QuickLink)
#define EXT_FIC_           "qic" // Backup set for Microsoft Backup
#define EXT_FIC_           "qif" // Quicken Interchange Format


#define EXT_FIC_           "qlb" // Quick library (MS C/C++)
#define EXT_FIC_           "qlc" // Data (PostScript help file) atmfonts.qlc
#define EXT_FIC_           "qlf" // Family Tree Maker Genealogy file
#define EXT_FIC_           "qlp" // Printer driver (QuickLink)
#define EXT_FIC_           "qm4" // Options or services file (QMail 4.x Mail Door)
#define EXT_FIC_           "qpr" // Generated query program (FoxPro)

#define EXT_FIC_           "qpw" // Quattro Pro Project file
#define EXT_FIC_           "qpx" // Compiled query program (FoxPro)
#define EXT_FIC_           "qrp" // Centura Report Builder file

#define EXT_FIC_           "qrs" // Equation Editor support file (WordPerfect for Win)
#define EXT_FIC_           "qrt" // Qrt ray tracing graphics
#define EXT_FIC_           "qry" // Query (dBASE IV)
#define EXT_FIC_           "qsd" // Quicken for Windows data file
#define EXT_FIC_           "qst" // Quake Spy Tab file
#define EXT_FIC_           "qt" //  Quicktime movie (animation)
#define EXT_FIC_           "qtc" // Incite Media Assistant file
#define EXT_FIC_           "qtk" // Apple QuickTake file format for Windows
#define EXT_FIC_           "qtp" // QuickTime Preferences

#define EXT_FIC_           "qts" // Macintosh PICT image

#define EXT_FIC_           "qtx" // QuickTime image
#define EXT_FIC_           "que" // CuteFTP Queue file

#define EXT_FIC_           "qvm" // Quake file 
#define EXT_FIC_           "qvs" // Casio Digital Camera file
#define EXT_FIC_           "qwk" // Qwk reader message file
#define EXT_FIC_           "qxd" // Document (QuarkXPress)
#define EXT_FIC_           "qxl" // Element library (QuarkXPress)
#define EXT_FIC_           "qxt" // Template file (QuarkXpress)
#define EXT_FIC_           "r" //   Ratfor (FORTRAN preprosessor) file
#define EXT_FIC_           "r33" // Train Simulator Game file
#define EXT_FIC_           "r8" //  Raw graphics (one byte per pixel) plane one (PicLab)
#define EXT_FIC_           "r8p" // Pcl 4 bitmap font file (Intellifont)
#define EXT_FIC_           "ra" //  Music (RealAudio)
#define EXT_FIC_           "ram" // Ramfile (RealAudio)
#define EXT_FIC_           "rar" // Compressed file archive created by RAR (rar1_402.exe)
#define EXT_FIC_           "rat" // Datafile (RATS)
#define EXT_FIC_           "raw" // Raw RGB 24-bit graphics
#define EXT_FIC_           "rbf" // Datafile (Rbase)
#define EXT_FIC_           "rbn" // Richard's Bridge Notation

#define EXT_FIC_           "rbx " // Format for playing RapidPlayer v3.0 ActiveX Control in Internet Explorer
#define EXT_FIC_           "rc" //  Resource script (MS C/C++ - Borland C++)

#define EXT_FIC_           "rcg" // Netscape newsgroup file (netsc.rcg)
#define EXT_FIC_           "rcp" // Recomposer's MIDI Sequencer Music file
#define EXT_FIC_           "rcx" // Lego Mindstorms Robotics Invention System
#define EXT_FIC_           "rdb" // TrueVector Rules database

#define EXT_FIC_           "rdf" // Compiled UIC source code (Geoworks UI Compiler)
#define EXT_FIC_           "rdi" // Device-independent bitmap file (RIFF RDIB format)
#define EXT_FIC_           "rds" // Ray Dream Studio file
#define EXT_FIC_           "rdx" // Datafile (Reflex)
#define EXT_FIC_           "rec" // Datafile (EpiInfo)


#define EXT_FIC_           "red" // Path info (Clarion Modula-2)
#define EXT_FIC_           "ref" // Cross-reference
#define EXT_FIC_           "reg" // Ole Registration (Windows 3.x)

#define EXT_FIC_           "rem" // Remarks
#define EXT_FIC_           "rep" // Qwk reader reply file

#define EXT_FIC_           "req" // Request
#define EXT_FIC_           "res" // Compiled resource (MS C/C++ - Borland C++)

#define EXT_FIC_           "rev" // Revision file (Geoworks)
#define EXT_FIC_           "rex" // Rexx source code file
#define EXT_FIC_           "rex" // Report definition (Oracle)
#define EXT_FIC_           "rez" // Resource file
#define EXT_FIC_           "rf" //  Sun raster graphics
#define EXT_FIC_           "rft" // Dca/RFT Revisable Format Text file (IBM DisplayWrite 4.0-5.1)
#define EXT_FIC_           "rgb" // Sgi RGB image file (SDSC Image Tool)
#define EXT_FIC_           "rgi" // RealArcade Game Installer
#define EXT_FIC_           "rgp" // RealArcade Game Package
#define EXT_FIC_           "rgs" // RealArcade Game Installer
#define EXT_FIC_           "rgx" // Symbol tables etc. info (ReaGeniX code generator)
#define EXT_FIC_           "rh" //  Resource header file (Borland C++ 4.5)
#define EXT_FIC_           "ri" //  Data (Lotus 1-2-3)
#define EXT_FIC_           "rib" // Graphics in Renderman format (3DReality)
#define EXT_FIC_           "ric" // Fax (Ricoh)
#define EXT_FIC_           "rif" // Riff bitmap graphics (Fractal Design Painter)
#define EXT_FIC_           "rip" // Graphics (Remote Access)
#define EXT_FIC_           "rix" // Bitmap graphics (ColorRIX VGA Paint)
#define EXT_FIC_           "rl4" // Bitmap graphics
#define EXT_FIC_           "rl8" // Bitmap graphics
#define EXT_FIC_           "rla" // Wavefront raster image file (SDSC Image Tool)
#define EXT_FIC_           "rlb" // Data (Harvard Graphics Win) hgw.rlb
#define EXT_FIC_           "rlc" // Graphics 1bit/pixel scanner output
#define EXT_FIC_           "rle" // Utah Run Length Encoded raster graphic (SDSC Image Tool)
#define EXT_FIC_           "rlz" // Realizer source code file (CA-Realizer)
#define EXT_FIC_           "rmf" // Rich Map Format
#define EXT_FIC_           "rmi" // Midi file (RIFF RMID format)
#define EXT_FIC_           "rmj" // Real Jukebox file
#define EXT_FIC_           "rmk" // Makefile (Clipper RMake)
#define EXT_FIC_           "rmm" // RealPlayer file
#define EXT_FIC_           "rmr" // Resume Maker file
#define EXT_FIC_           "rmx" // RealJukeBox MP3 file
#define EXT_FIC_           "rn" //  Xpl program for Nota Bene users
#define EXT_FIC_           "rnd" // Rendering Slide (AutoCAD AutoShade)
#define EXT_FIC_           "roi" // Actuate ReportBlast file.rnoRunoff file (VAX)
#define EXT_FIC_           "rol" // Fm music Adlib Music File (Roland)
#define EXT_FIC_           "rpd" // Database (RapidFile)


#define EXT_FIC_           "rpl" // Text document (Replica)
#define EXT_FIC_           "rpm" // RedHat Package Manager


#define EXT_FIC_           "rps" // Propellerhead Software Reason Song
#define EXT_FIC_           "rpt" // Report
#define EXT_FIC_           "rrd" // ERDAS Imagine file
#define EXT_FIC_           "rs_" // Resource fork of a Macintosh file (Mac-ette)
#define EXT_FIC_           "rsb" // Red Storm Image Format
#define EXT_FIC_           "rsc" // Resource file
#define EXT_FIC_           "rsm" // ReliaSoft MPC 3


#define EXT_FIC_           "rsp" // Response file
#define EXT_FIC_           "rss" // Rockwell Logix PLC file
#define EXT_FIC_           "rst" // ANSYS Results

#define EXT_FIC_           "rsw" // ReliaSoft BlockSim
#define EXT_FIC_           "rtf" // Rich Text Format text file (many - Windows Word)

#define EXT_FIC_           "rtl" // Run Time Library (NU 7.0)

#define EXT_FIC_           "rtp" // Rtpatch software update package data file
#define EXT_FIC_           "rts" // Runtime library file (CA-Realizer)
#define EXT_FIC_           "rtx" // Reliacast Audience Manager Turnstile

#define EXT_FIC_           "rul" // InstallShield
#define EXT_FIC_           "rvp" // MS Scan Configuration file
#define EXT_FIC_           "rvw" // Review
#define EXT_FIC_           "rws" // Resource Workshop data file (Borland C++)
#define EXT_FIC_           "rwx" // Script (RenderWare)
#define EXT_FIC_           "rwz" // MS Outlook Rules Wizard file
#define EXT_FIC_           "rzr" // in-sync Speed Razor Project file
#define EXT_FIC_           "rzx" // in-sync Speed Razor Project file
#define EXT_FIC_           "s" //   Assembly source code file (unix)

#define EXT_FIC_           "s$$" // Temporary sort file (Sprint)
#define EXT_FIC_           "s3m" // Music (16 channels) (Scream Tracker 3.0)
#define EXT_FIC_           "sac" // Shared Asset Catalog (Adobe)
#define EXT_FIC_           "saf" // MusicMatch Jukebox Secure Audio file


#define EXT_FIC_           "sah" // SETI@Home data file
#define EXT_FIC_           "sal" // Datafile (SORITEC)
#define EXT_FIC_           "sam" // Text file (Samna - Lotus Ami/Ami Pro)
#define EXT_FIC_           "sar" // Compressed file archive created by SAR (sar1.zip)
#define EXT_FIC_           "sav" // Backup file (saved file)


#define EXT_FIC_           "sb" //  Audio file (signed byte)
#define EXT_FIC_           "sbc" // Sagebrush Corporation Spectrum CIRC/CAT Report
#define EXT_FIC_           "sbd" // Storyboard (Storyboard Editor)
#define EXT_FIC_           "sbi" // Sound Blaster Instrument file (Creative Labs)
#define EXT_FIC_           "sbp" // Dml program (Superbase 4)
#define EXT_FIC_           "sbr" // Support file (Source Browser)
#define EXT_FIC_           "sbs" // SWAT HRU Output file
#define EXT_FIC_           "sbt" // Notes related to record (Suberbase 4 Windows)
#define EXT_FIC_           "sc" //  Pal script (Paradox)

#define EXT_FIC_           "sc3" // Renamed dBASE III screen mask file (dBASE IV)

#define EXT_FIC_           "sca" // Datafile (SCA)
#define EXT_FIC_           "scc" // Text file
#define EXT_FIC_           "scd" // Scodl Scan Conversion Object Description Language graphics
#define EXT_FIC_           "scf" // Multimedia show (ScoreMaker)

#define EXT_FIC_           "sch" // Project schedule (Schedule Publisher)

#define EXT_FIC_           "sci" // System Configuration Information

#define EXT_FIC_           "scm" // Scheme source code file

#define EXT_FIC_           "scn" // Screen file (Kermit)
#define EXT_FIC_           "sco" // High score
#define EXT_FIC_           "scp" // Script (BITCOM)
#define EXT_FIC_           "scr" // Debug source code file (DOS Debug)

#define EXT_FIC_           "sct" // Screen memo (FoxPro)
#define EXT_FIC_           "scx" // Bitmap graphics (ColorRIX)


#define EXT_FIC_           "scy" // Security file (ReaGeniX)
#define EXT_FIC_           "sda" // Fidonet's Software Distribution Network file archive description
#define EXT_FIC_           "sdc" // StarOffice Spreadsheet
#define EXT_FIC_           "sdd" // StarOffice Presentation
#define EXT_FIC_           "sdf" // System Data Format file (fixed lenght ASCII text)
#define EXT_FIC_           "sdi" // Software Distribution Network Info file
#define EXT_FIC_           "sdn" // Software Distribution Network compressd file archive (pak251.exe)
#define EXT_FIC_           "sdr" // SmartDraw file
#define EXT_FIC_           "sdt" // SmartDraw Template


#define EXT_FIC_           "sdu" // Edwards Systems Technology file 
#define EXT_FIC_           "sdw" // StarOffice Text


#define EXT_FIC_           "sea" // Self-Extracting compressed Macintosh file Archive
#define EXT_FIC_           "sec" // CyberPaint animation file (sequence) 


#define EXT_FIC_           "sep" // Printer separator page
#define EXT_FIC_           "seq" // Atari animation file

#define EXT_FIC_           "ses" // Session info (Clarion Modula-2)
#define EXT_FIC_           "set" // Configuration (1st Reader)


#define EXT_FIC_           "sf" //  Ircam Sound File (CSound package - MixView sound sample editor)

#define EXT_FIC_           "sff" // Fritz Fax-Print file


#define EXT_FIC_           "sfi" // Graphics (SIS Framegrabber)

#define EXT_FIC_           "sfl" // Pcl 4 bitmap font (landscape) (Intellifont) (Ventura Publisher)
#define EXT_FIC_           "sfn" // Font (SPX)
#define EXT_FIC_           "sfp" // Pcl 4 bitmap font (portrait) (Intellifont) (Ventura Publisher)
#define EXT_FIC_           "sfs" // Pcl 5 scalable font file (Intellifont)
#define EXT_FIC_           "sft" // Screen font (ChiWriter)
#define EXT_FIC_           "sfv" // QuickSFV/WinSFV Checksum file

#define EXT_FIC_           "sfw" // Seattle Film Works file
#define EXT_FIC_           "sg1" // Graphics (Stanford Graphics)
#define EXT_FIC_           "sgf" // Document with graphics (Starwriter)


#define EXT_FIC_           "sgi" // Graphics (IRIS - Silicon Graphics)
#define EXT_FIC_           "sgm " // Run-Time Help Files


#define EXT_FIC_           "sgn" // Sierra Print Artist Sign
#define EXT_FIC_           "sgp" // Statistics (STATGRAPHICS Plus)
#define EXT_FIC_           "sgt" // Save/get keyboard macro (Signature)
#define EXT_FIC_           "sh" //  Unix shell script

#define EXT_FIC_           "sh3" // Presentation (Harvard Graphics 3.0)
#define EXT_FIC_           "shb" // Background (CorelShow)
#define EXT_FIC_           "shd" // Print Spooler Shadow file
#define EXT_FIC_           "shg" // Segmented-graphics bitmap
#define EXT_FIC_           "shk" // Compressed Apple II file archive created by SHRINKIT
#define EXT_FIC_           "shm" // Shell macro (WordPerfect Library)
#define EXT_FIC_           "shn" // Shorten audio compression file
#define EXT_FIC_           "shr" // Unix ASCII file archive created by SHAR (unshar.zip)
#define EXT_FIC_           "shs" // Scrap Object
#define EXT_FIC_           "shtml  HTML File with Server Side .shw" // Presentation (Harvard Graphics 2.0 - CorelShow)

#define EXT_FIC_           "sid" // Commodore64 Music file

#define EXT_FIC_           "sif" // Setup Installation Files info (Windows NT Setup)
#define EXT_FIC_           "sig" // Current program settings (Signature)


#define EXT_FIC_           "sik" // Backup file (Sicherungskopie) (MS Word)
#define EXT_FIC_           "sim" // Aurora



#define EXT_FIC_           "sis" // SymbianOS Installer file
#define EXT_FIC_           "sit" // Compressed Macintosh archive created by STUFFIT (unsit30.zip)
#define EXT_FIC_           "skb " // SketchUp software file (3D Design Tool)
#define EXT_FIC_           "skf" // Autosketch file
#define EXT_FIC_           "skn" // Interface skins images (FileWrangler, SecurDesk!, SecurDesk! LV, ZipWrangler)
#define EXT_FIC_           "skp " // Sketchup software component (3D Design Tool)
#define EXT_FIC_           "sl" //  S-Lang source code file
#define EXT_FIC_           "slb" // Slide library (AutoCAD)
#define EXT_FIC_           "slc" // Compiled SALT script (Telix)
#define EXT_FIC_           "sld" // Slide (AutoCAD)
#define EXT_FIC_           "sli" // Slide (MAGICorp Slide Service)
#define EXT_FIC_           "slk" // Sylk Symbolic Link format data file (MultiPlan)
#define EXT_FIC_           "sll" // Sound data file
#define EXT_FIC_           "slt" // Salt Script Application Language for Telix script source (Telix)
#define EXT_FIC_           "sm" //  Smalltalk source code file
#define EXT_FIC_           "smc" // Super Nintendo Game-console ROM Image
#define EXT_FIC_           "smd" // StarOffice Mail
#define EXT_FIC_           "smf" // Fax (SMARTFAX)
#define EXT_FIC_           "smi" // RealPlay SMIL file

#define EXT_FIC_           "smk" // Compressed File (Smacker)
#define EXT_FIC_           "smm" // Macro (Ami Pro)
#define EXT_FIC_           "smp" // Sample (sound file)
#define EXT_FIC_           "sms" // Microsoft Package Definition file

#define EXT_FIC_           "smt" // Text file (Smart Ware II)
#define EXT_FIC_           "snd" // Digitized sound file (Macintosh/ATARI/PC)
#define EXT_FIC_           "sng" // Song (midi sound) (Midisoft Studio - Prism)
#define EXT_FIC_           "snm" // Netscape mail
#define EXT_FIC_           "sno" // Snobol4 source code file
#define EXT_FIC_           "snp" // CoffeeCup HTML Editor Snippet



#define EXT_FIC_           "snx" // Mirage Microdrive Snapshot Extended Version


#define EXT_FIC_           "sol" // Solution eg. game walkthroughs
#define EXT_FIC_           "som" // Network serial numbers (Quattro Pro)

#define EXT_FIC_           "son" // Song (SBStudio II)
#define EXT_FIC_           "sou" // Sound data (sound tool)
#define EXT_FIC_           "sp" //  Compressed file archive created by SPLINT (unix)
#define EXT_FIC_           "spa" // Macromedia FutureSplash file



#define EXT_FIC_           "spc" // Program (MS Multiplan)


#define EXT_FIC_           "spd" // Scalable font (Speedo) (Harvard Graphics 3.0)
#define EXT_FIC_           "spf" // Slide presentation file (EnerGraphics)
#define EXT_FIC_           "spg" // Glossary (Sprint)
#define EXT_FIC_           "spi" // Graphics (Siemens and Philips scanner)
#define EXT_FIC_           "spl" // Compressed file archive created by SPLINT (splint.arc)

#define EXT_FIC_           "spm" // Data (WordPerfect) wp{wp}.spm
#define EXT_FIC_           "spo" // Statistical Program (SPSS)
#define EXT_FIC_           "spp" // Printer file (Sprint)
#define EXT_FIC_           "spr" // Document letter (Sprint)


#define EXT_FIC_           "sps" // Spssx source code file (VAX/VMS)

#define EXT_FIC_           "spt" // Spitbol source code file

#define EXT_FIC_           "spw" // Worksheet (SigmaPlot)
#define EXT_FIC_           "spx" // Compiled screen program (FoxPro)
#define EXT_FIC_           "sql" // SQL report or query
#define EXT_FIC_           "sqz" // Compressed file archive created by SQUEEZE (sqz1083e.exe)
#define EXT_FIC_           "src" // Source (DataFlex)
#define EXT_FIC_           "srf" // Sun Raster File graphics
#define EXT_FIC_           "srp" // Script (QuickLink)
#define EXT_FIC_           "srt" // BSplayer Subtitle file


#define EXT_FIC_           "ss" //  Bitmap graphics (Splash)
#define EXT_FIC_           "ssa" // Subtitles
#define EXT_FIC_           "ssb" // SmartSync Pro 
#define EXT_FIC_           "ssd" // Datafile (SAS/PC)
#define EXT_FIC_           "ssf" // Enable Spreadsheet file
#define EXT_FIC_           "ssm" // RealPlayer Standard Streaming Metafile
#define EXT_FIC_           "ssp" // Datafile (SAS Transport)
#define EXT_FIC_           "st" //  Smalltalk source code file (Little Smalltalk)


#define EXT_FIC_           "st3" // MIDI Karaoke file
#define EXT_FIC_           "sta" // Saved state (Reflection 4.0)

#define EXT_FIC_           "stb" // Stub library (Genus GX Kernel)
#define EXT_FIC_           "std" // State Transition Diagram graphic file (Prosa)

#define EXT_FIC_           "stf" // Compressed file archive created by SHRINKTOFIT
#define EXT_FIC_           "stg " // ActiveSync (Microsoft)
#define EXT_FIC_           "stm" // State Transition Diagram model file (Prosa)

#define EXT_FIC_           "stn" // ArcView Geocoding Standardization file

#define EXT_FIC_           "sto" // Pascal stub OBJ file (Genus GX Kernel)
#define EXT_FIC_           "stp" // PageKeeper Packed Storage file


#define EXT_FIC_           "str" // Structure list object file (dBASE Application Generator)
#define EXT_FIC_           "sts" // Project status info (MS C/C++)

#define EXT_FIC_           "stt" // Automap Template

#define EXT_FIC_           "stu" // Tarantella Enterprise 3 3270 Emulator Style file

#define EXT_FIC_           "stw" // Data file (SmartTerm for Windows)
#define EXT_FIC_           "stx" // Electronic book (SmarText)

#define EXT_FIC_           "sty" // Style library or sheet (many text and graphics programs)
#define EXT_FIC_           "sub" // CloneCd related file
#define EXT_FIC_           "sui" // Suit library (Simple User Interface Toolkit)
#define EXT_FIC_           "sum" // Summary
#define EXT_FIC_           "sun" // Sun rasterfile graphics
#define EXT_FIC_           "sup" // Supplementary dictionary (WordPerfect for Win)
#define EXT_FIC_           "sv4" // RollerCoaster Tycoon Saved Game
#define EXT_FIC_           "svd" // Autosave file for document (MS Word)
#define EXT_FIC_           "svg" // Autosave file for glossary (MS Word)
#define EXT_FIC_           "svp" // WISCO Survey Power


#define EXT_FIC_           "svs" // Autosave file for style sheet (MS Word)
#define EXT_FIC_           "sw" //  Audio file (signed word)
#define EXT_FIC_           "swd" // Storybook file 

#define EXT_FIC_           "swf" // ShockWave Flash object
#define EXT_FIC_           "swg" // Swag packet (SWAG Reader)
#define EXT_FIC_           "swi" // Swish Data file
#define EXT_FIC_           "swk" // Swapkeys Keyboard File
#define EXT_FIC_           "swp" // Document backup (Sprint)

#define EXT_FIC_           "sxw" // OpenOffice.org Writer 6.0 text file

#define EXT_FIC_           "sy1" // Smartpix symbol library (Ami Pro)
#define EXT_FIC_           "sy3" // Symbol file (Harvard Graphics 3.0)
#define EXT_FIC_           "syd" // Backup of startup files created by QEMM (?) autoexec.syd
#define EXT_FIC_           "sym" // Precompiled headers (Borland C++)


#define EXT_FIC_           "syn" // Sdsc Synu image file (SDSC Image Tool)

#define EXT_FIC_           "sys" // Datafile (SYGRAPH - SYSTAT - SPSS/PC)

#define EXT_FIC_           "syw" // Graphics symbols (Harvard Graphics Win)
#define EXT_FIC_           "t" //   Tads source


#define EXT_FIC_           "t44" // Temporary file for Sort or Index (dBASE IV)
#define EXT_FIC_           "t64" // Program (C64S emulator)
#define EXT_FIC_           "tab" // Guitar Tablature file


#define EXT_FIC_           "tag" // Query tag name (DataFlex)
#define EXT_FIC_           "tah" // Turbo Assembler Help file (Borland C++)
#define EXT_FIC_           "tal" // Text illustration (TypeAlign)
#define EXT_FIC_           "tao" // IsoBuster file
#define EXT_FIC_           "tar" // Compressed file archive created by TAR (pax2exe.zoo)
#define EXT_FIC_           "tax" // TurboTax file
#define EXT_FIC_           "taz" // Compressed ASCII file archive created by TAR and COMPRESS (.tar.Z)
#define EXT_FIC_           "tb1" // Font file (Borland Turbo C)
#define EXT_FIC_           "tb2" // Font file (Borland Turbo C)
#define EXT_FIC_           "tbf" // Fax (Imavox TurboFax)
#define EXT_FIC_           "tbh" // Mah Jongg for Windows Tile Set
#define EXT_FIC_           "tbk" // Memo backup (dBASE IV - FoxPro)

#define EXT_FIC_           "tbl" // Graphics (native format) (PageMaker TableEditor)

#define EXT_FIC_           "tbs" // Text elements ?? (Textbausteine) (MS Word)
#define EXT_FIC_           "tbx" // Table (Project Scheduler 4)
#define EXT_FIC_           "tc" //  Configuration (Turbo C - Borland C++)
#define EXT_FIC_           "tch" // Turbo C Help file (Borland C++)
#define EXT_FIC_           "tcl" // Tool Command Language source code (Swat)
#define EXT_FIC_           "tcw" // Drawing (TurboCAD for Windows)
#define EXT_FIC_           "td" //  Configuration file (Turbo Debugger for DOS)
#define EXT_FIC_           "td0" // Disk image file (Teledisk)
#define EXT_FIC_           "td2" // Configuration file (Turbo Debugger for Win32)
#define EXT_FIC_           "tdb" // Database (TACT)
#define EXT_FIC_           "tdf" // Font (TheDraw)

#define EXT_FIC_           "tdh" // Help file (Turbo Debugger)
#define EXT_FIC_           "tdk" // Keystroke recording file (Turbo Debugger)
#define EXT_FIC_           "tds" // Symbol table (Turbo Debugger)
#define EXT_FIC_           "tdt" // ASCII Data File in CSV Format 

#define EXT_FIC_           "tdw" // Configuration file (Turbo Debugger for Windows)
#define EXT_FIC_           "tee" // TeeChart Office graphic
#define EXT_FIC_           "tef" // Fax (Relisys TEFAX)
#define EXT_FIC_           "tel" // Host file (Telnet)
#define EXT_FIC_           "tem" // Turbo Editor Macro Language script (Borland C++)

#define EXT_FIC_           "tex" // Tex text file (Scientific Word)

#define EXT_FIC_           "tf" //  Configuration (Turbo Profiler)
#define EXT_FIC_           "tfa" // Area file (Turbo Profiler)
#define EXT_FIC_           "tfc" // Catalogue file (Tobi's Floppy Cataloguer)
#define EXT_FIC_           "tfh" // Help file (Turbo Profiler)
#define EXT_FIC_           "tfm" // Tex Font Metric file (TeX)

#define EXT_FIC_           "tfs" // Statistics (Turbo Profiler)
#define EXT_FIC_           "tfw" // ArcView World File For TIF Image

#define EXT_FIC_           "tg1" // Project file (On Target)
#define EXT_FIC_           "tga" // Truevision Targa bitmap graphics
#define EXT_FIC_           "tgz" // Compressed file archive created by TAR and GNUzip (.tar.gz)
#define EXT_FIC_           "thb" // KinuPix Skin
#define EXT_FIC_           "thd" // Thread
#define EXT_FIC_           "thm" // Microsoft Clipart Gallery database

#define EXT_FIC_           "thn" // Graphics Workshop for Windows Thumbnail
#define EXT_FIC_           "ths" // Thesaurus dictionary (WordPerfect for Win)
#define EXT_FIC_           "tif" // Tagged Image File Format bitmap graphics (PageMaker - CorelDRAW)
#define EXT_FIC_           "til" // Fuzzy logic knowledge base (Togai InfraLogic Fuzzy-C Compiler)
#define EXT_FIC_           "tim" // Playstation Game Texture Image

#define EXT_FIC_           "tis" // Tile set (MahJongg 3.0)
#define EXT_FIC_           "tix" // ASA for UNIX Terminfo Extension file
#define EXT_FIC_           "tjl" // Backup file (VAXTPU editor)
#define EXT_FIC_           "tlb" // Reference table (Bubble Chamber)

#define EXT_FIC_           "tlb" // Type library (Visual C++)
#define EXT_FIC_           "tlc" // Compiled Tool Command Language source code (Swat)
#define EXT_FIC_           "tlp" // Project (TimeLine)
#define EXT_FIC_           "tlt" // Trellix Web Design file
#define EXT_FIC_           "tmb" // Timbuktu Pro Connection Document
#define EXT_FIC_           "tmd" // Document (TextMaker)
#define EXT_FIC_           "tmf" // Tagged Font Metric file (WordPerfect for Win)
#define EXT_FIC_           "tmo" // Ztg global optimizer default output file (Zortech C++)
#define EXT_FIC_           "tmp" // Temporary file
#define EXT_FIC_           "tmq" // TestMaster file
#define EXT_FIC_           "tms" // Script (Telemate)
#define EXT_FIC_           "tmv" // Template (TextMaker)
#define EXT_FIC_           "toc" // Table Of Contents
#define EXT_FIC_           "tol" // Kodak Photoenhancer
#define EXT_FIC_           "tos" // Self-extracting file archive (Atari ST)
#define EXT_FIC_           "tp" //  Configuration (Turbo Pascal)

#define EXT_FIC_           "tp3" // Template (Harvard Graphics 3.0)
#define EXT_FIC_           "tpb" // Downloadable PCL Soft font file backup (HiJaak)
#define EXT_FIC_           "tpf" // Downloadable PCL Soft font file (HiJaak)
#define EXT_FIC_           "tph" // Help file (Turbo Pascal)
#define EXT_FIC_           "tpl" // Resident units library (Turbo Pascal)

#define EXT_FIC_           "tpp" // Protected Mode Units (Borland Pascal 7.0)
#define EXT_FIC_           "tps" // Clarion for Windows data file
#define EXT_FIC_           "tpu" // Turbo Pascal Unit (BGI) (Turbo Pascal)

#define EXT_FIC_           "tpw" // Session-state file (Turbo Profiler for Windows)

#define EXT_FIC_           "tpz" // Compressed file archive created by TAR and GNUzip (.tar.gz)
#define EXT_FIC_           "tr" //  Session-state settings (Turbo Debugger for DOS)

#define EXT_FIC_           "tr2" // Session-state settings (Turbo Debugger for Win32)
#define EXT_FIC_           "trace" // ECXpert Debugging file

#define EXT_FIC_           "trc" // Debug support file (Power CTrace)
#define EXT_FIC_           "tre" // Directory tree file (PC-Tools)
#define EXT_FIC_           "trg" // Symantec LiveUpdate file
#define EXT_FIC_           "tri" // Trigram file
#define EXT_FIC_           "trk" // Kermit Script file

#define EXT_FIC_           "trm" // Terminal settings (Windows 3.x)
#define EXT_FIC_           "trn" // Translation support file (Quattro)
#define EXT_FIC_           "trp" // Tripmaker file
#define EXT_FIC_           "trs" // Executable file (Micrografx)
#define EXT_FIC_           "trw" // Session-state settings (Turbo Debugger for Windows)
#define EXT_FIC_           "trx" // Emerald PC Authorize Batch Transaction file
#define EXT_FIC_           "tsk" // Skins for Pocket PC PDAs

#define EXT_FIC_           "tsp" // Windows Telephony Service Provider
#define EXT_FIC_           "tst" // Printer test file (WordPerfect for Win)
#define EXT_FIC_           "tub" // PaintShop Pro Tube file
#define EXT_FIC_           "tut" // Tutorial
#define EXT_FIC_           "tv" //  Table view settings (Paradox)
#define EXT_FIC_           "tv1" // Overflow file above insert point in Doc 1 (WordPerfect for Win)
#define EXT_FIC_           "tv2" // Overflow file above insert point in Doc 2 (WordPerfect for Win)
#define EXT_FIC_           "tv3" // Overflow file above insert point in Doc 3 (WordPerfect for Win)
#define EXT_FIC_           "tv4" // Overflow file above insert point in Doc 4 (WordPerfect for Win)
#define EXT_FIC_           "tv5" // Overflow file above insert point in Doc 5 (WordPerfect for Win)
#define EXT_FIC_           "tv6" // Overflow file above insert point in Doc 6 (WordPerfect for Win)
#define EXT_FIC_           "tv7" // Overflow file above insert point in Doc 7 (WordPerfect for Win)
#define EXT_FIC_           "tv8" // Overflow file above insert point in Doc 8 (WordPerfect for Win)
#define EXT_FIC_           "tv9" // Overflow file above insert point in Doc 9 (WordPerfect for Win)
#define EXT_FIC_           "tvf" // Table view settings (dBASE)
#define EXT_FIC_           "tvo" // TeveoLive
#define EXT_FIC_           "tvp" // NVIDIA Graphic Card Update file
#define EXT_FIC_           "tvt" // RealPlayer
#define EXT_FIC_           "txd" // Grand Theft Auto 3 Texture file

#define EXT_FIC_           "txf" // Compressed file archive created by TAR and FREEZE (.tar.f)
#define EXT_FIC_           "txi" // Support file (TeX)
#define EXT_FIC_           "txl" // Genesis3D Texture file
#define EXT_FIC_           "tym" // Time Stamp (PageMaker 4)
#define EXT_FIC_           "tz" //  Compressed file archive created by TAR and COMPRESS (.tar.Z)
#define EXT_FIC_           "tzb" // Compressed file archive created by TAR - COMPRESS - BTOA (.tar.Z.btoa)
#define EXT_FIC_           "uax" // Unreal Audio file
#define EXT_FIC_           "ub" //  Audio file (unsigned byte)
#define EXT_FIC_           "uc2" // Compressed file archive created by UltraCompressor II (uc2.zip)
#define EXT_FIC_           "ucn" // New compressed file archive created by UltraCompressor II
#define EXT_FIC_           "ucs" // Universal Classification Standard Database file
#define EXT_FIC_           "udc" // Acrobat Spelling file
#define EXT_FIC_           "udf" // Filter (Photostyler)
#define EXT_FIC_           "udl" // MS Data Link
#define EXT_FIC_           "uds" // Sierra Generations Family file
#define EXT_FIC_           "ue2" // Encrypted file archive created by UltraCompressor II
#define EXT_FIC_           "ufo" // Ulead Object file
#define EXT_FIC_           "uha" // UHARC Compressed Archive
#define EXT_FIC_           "uhs" // Universal Hint System (binary file)
#define EXT_FIC_           "ui" //  Espire source code file (Geoworks UI Compiler)

#define EXT_FIC_           "uif" // Long prompts for windows (WordPerfect for Win)
#define EXT_FIC_           "uih" // Espire header file (Geoworks UI Compiler)
#define EXT_FIC_           "ul" //  Ulaw audio file
#define EXT_FIC_           "uld" // Information about uploaded files (Procomm Plus)
#define EXT_FIC_           "ult" // Music (UltraTracker)
#define EXT_FIC_           "umb" // Backup file (MemMaker)
#define EXT_FIC_           "umx" // Unreal music file
#define EXT_FIC_           "uni" // Unimod music module (MIKMOD)

#define EXT_FIC_           "unq" // Fax View file 
#define EXT_FIC_           "unx" // Text file containing UNIX specific info
#define EXT_FIC_           "upd" // Program update info

#define EXT_FIC_           "upo" // Compiled update data (dBASE)
#define EXT_FIC_           "upx" // ULead Photo Express Saved Image file
#define EXT_FIC_           "usb" // D-Link FM Radio Update

#define EXT_FIC_           "usp" // Printer font with USASCII extended character set (PageMaker)
#define EXT_FIC_           "usr" // User database file (Procomm Plus - Turbo C++ tour)
#define EXT_FIC_           "utf" // AOL Updating Files 
#define EXT_FIC_           "utl" // Sound file
#define EXT_FIC_           "utx" // Unreal Texture file

#define EXT_FIC_           "uu" //  Compressed ASCII file archive created by UUDE/ENCODE
#define EXT_FIC_           "uue" // Compressed ASCII file archive created by UUENCODE (uuexe515.exe)
#define EXT_FIC_           "uvr" // Ulead Cool 360 Viewer file
#define EXT_FIC_           "uw" //  Audio file (unsigned word)
#define EXT_FIC_           "uwl" // WordPerfect User word list
#define EXT_FIC_           "v" //   Consistency check support file (ReaGeniX code generator)

#define EXT_FIC_           "v64" // Nintento 64 Emulation ROM Image 
#define EXT_FIC_           "val" // Validity checks and referential integrity (Paradox for Windows)

#define EXT_FIC_           "van" // Animation (VistaPro)
#define EXT_FIC_           "var" // Variable file (IconAuthor)
#define EXT_FIC_           "vbc" // Visual Business Cards
#define EXT_FIC_           "vbd" // ActiveX file
#define EXT_FIC_           "vbe" // VBScript Encoded Script file
#define EXT_FIC_           "vbn" // Norton Corporate anti-virus quarantined file 
#define EXT_FIC_           "vbp" // Visual Basic Project
#define EXT_FIC_           "vbs" // Visual Basic Script file (Visual Basic)
#define EXT_FIC_           "vbw" // Visual Basic Project Workplace (Visual Basic)
#define EXT_FIC_           "vbx" // Visual Basic eXtension (Visual Basic)
#define EXT_FIC_           "vc" //  Include file with color definitions (Vivid 2.0)

#define EXT_FIC_           "vcd" // VisualCADD Drawing file

#define EXT_FIC_           "vcf" // VCard file
#define EXT_FIC_           "vch" // Interlock Public Computer Utility
#define EXT_FIC_           "vcw" // Visual workbench information (MS Visual C++)
#define EXT_FIC_           "vcx" // Spreatsheet (VisiCalc Advanced)
#define EXT_FIC_           "vda" // Bitmap graphics
#define EXT_FIC_           "vdb" // Norton AntiVirus Corporate Edition Update file

#define EXT_FIC_           "vdf" // AntiVir virus definition file

#define EXT_FIC_           "vdm" // VDM Play
#define EXT_FIC_           "vdr" // Drawing (ComputerEasy Draw)
#define EXT_FIC_           "vdx" // XML for Visio Drawing file


#define EXT_FIC_           "vem" // VeePro Embroidery Software Format

#define EXT_FIC_           "vew" // View file (Clipper 5, Lotus Approach)
#define EXT_FIC_           "vfm" // Voting Form (Voter)
#define EXT_FIC_           "vfn" // Voting Form for Customers (Voter)
#define EXT_FIC_           "vfp" // TMPGEnc VFAPI Plug-in
#define EXT_FIC_           "vfx" // Ulead Video Studio Sample file
#define EXT_FIC_           "vga" // Vga display driver

#define EXT_FIC_           "vgd" // Vga display driver (Generic CADD)
#define EXT_FIC_           "vgr" // Graphics (Ventura Publisher)
#define EXT_FIC_           "vi" //  Graphics (Jovian Logic VI)
#define EXT_FIC_           "vic" // Vicar graphics
#define EXT_FIC_           "vid" // Ms-DOS Shell Monitor file (MS-DOS 5)


#define EXT_FIC_           "vif" // Khoros Visualization image file (SDSC Image Tool)
#define EXT_FIC_           "vik" // Viking graphics
#define EXT_FIC_           "vir" // Virus Infected file 
#define EXT_FIC_           "vis" // Vis graphics
#define EXT_FIC_           "viv" // VivoActive Player Video file
#define EXT_FIC_           "vlm" // Ashlar-Vellum file


#define EXT_FIC_           "vm" //  Virtual Memory file (Geoworks)
#define EXT_FIC_           "vm1" // Panasonic SD Voice Editor file
#define EXT_FIC_           "vmc" // Virtual memory configuration (Acrobat reader)
#define EXT_FIC_           "vmf" // Font characteristics (Ventura Publisher)

#define EXT_FIC_           "vml" // Vector Markup Language
#define EXT_FIC_           "vmo" // Mobile Phone voice file (Siemens Sl45)


#define EXT_FIC_           "vmp" // Logos Library System 2.x Verse Map
#define EXT_FIC_           "vms" // Text file containing VMS specific info
#define EXT_FIC_           "vo" //  Include file with object definition (Vivid 2.0)
#define EXT_FIC_           "vob" // DVD video movie file
#define EXT_FIC_           "voc" // Digitized samples (Creative Voice file)
#define EXT_FIC_           "vof" // Object folder (VZ Programmer)
#define EXT_FIC_           "vol" // Tribes 2 game file


#define EXT_FIC_           "vor" // OpenOffice.org Template
#define EXT_FIC_           "vox" // Vox Audio

#define EXT_FIC_           "vpa" // Excite Chat Gestures file
#define EXT_FIC_           "vpd" // Virpet Performance Descriptor

#define EXT_FIC_           "vpg" // Graphics (VPGraphics)
#define EXT_FIC_           "vpp" // Virtual Pool Game

#define EXT_FIC_           "vqe" // Yamaha Sound-VQ Locator File
#define EXT_FIC_           "vqf" // Yamaha Sound-VQ File
#define EXT_FIC_           "vql" // Yamaha Sound-VQ Locator File
#define EXT_FIC_           "vrd" // VRScape data file
#define EXT_FIC_           "vrm" // Overlay file (QuattroPro)
#define EXT_FIC_           "vro" // Panasonic DVD Recorder file
#define EXT_FIC_           "vrp" // Project (WATCOM VX.Rexx)
#define EXT_FIC_           "vrs" // Video Resource eg. video device driver (WordPerfect)
#define EXT_FIC_           "vs" //  Include file with surface definition (Vivid 2.0)
#define EXT_FIC_           "vsd" // Diagram (Shapeware Visio)
#define EXT_FIC_           "vsl" // GetRight Download List file

#define EXT_FIC_           "vsm" // Simulation model (VisSim)
#define EXT_FIC_           "vsp" // Sprite (SPX)
#define EXT_FIC_           "vss" // Smartshapes file (Shapeware Visio)
#define EXT_FIC_           "vst" // Truevision Vista bitmap graphics
#define EXT_FIC_           "vtx" // XML for Visio template file
#define EXT_FIC_           "vue" // Animation (3D Studio)

#define EXT_FIC_           "vw" //  Text file (Volkswriter)
#define EXT_FIC_           "vw3" // Text file (Volkswriter 3)
#define EXT_FIC_           "vwl" // VideoWave Video Wave Library 
#define EXT_FIC_           "vwr" // File viewer file (PC Tools)
#define EXT_FIC_           "vwt" // VideoWave Thumbnail
#define EXT_FIC_           "vxd" // Virtual device driver (MS Windows)
#define EXT_FIC_           "vyd" // VyperHelp
#define EXT_FIC_           "w" //   Word chart file (APPLAUSE)
#define EXT_FIC_           "w30" // Printer font (AST TurboLaser) (Ventura Publisher)
#define EXT_FIC_           "w31" // Startup file (Windows 3.1)
#define EXT_FIC_           "w3g" // Warcraft III file
#define EXT_FIC_           "w3m" // Warcraft III Map file
#define EXT_FIC_           "w44" // Temporary file for Sort or Index (dBASE)
#define EXT_FIC_           "wab" // Outlook File
#define EXT_FIC_           "wac" // Infinity Game Engine WAVC Sound
#define EXT_FIC_           "wad" // Doom Game file

#define EXT_FIC_           "waf" // Mayim's WAF Compiler file
#define EXT_FIC_           "wal" // WalMaster Showlist file
#define EXT_FIC_           "war" // Java Web Archive

#define EXT_FIC_           "wav" // Waveform audio file (RIFF WAVE format)
#define EXT_FIC_           "wb1" // Notebook (Quattro Pro)
#define EXT_FIC_           "wb2" // Spreadsheet (Quattro Pro)
#define EXT_FIC_           "wb3" // Quattro Pro for Windows
#define EXT_FIC_           "wba" // WindowBlinds Compressed Skin

#define EXT_FIC_           "wbc" // Webshots Picture Collection
#define EXT_FIC_           "wbf" // Ms Windows Batch File (Catch)
#define EXT_FIC_           "wbk" // Document/workbook (WordPerfect for Win)
#define EXT_FIC_           "wbt" // Batch file (WinBatch)
#define EXT_FIC_           "wbx" // Webigger file
#define EXT_FIC_           "wbz" // WebShots file
#define EXT_FIC_           "wcd" // Macro token list (WordPerfect for Win)
#define EXT_FIC_           "wcm" // Data transmission file (MS Works)

#define EXT_FIC_           "wcp" // Product information description (WordPerfect for Win)
#define EXT_FIC_           "wd2" // Info Select for Palm Organizer file

#define EXT_FIC_           "wdb" // Database (MS Works)
#define EXT_FIC_           "wdf" // ReliaSoft Weibull 5.0

#define EXT_FIC_           "wdl" // Windows XP Watchdog Log file
#define EXT_FIC_           "web" // Web source code file
#define EXT_FIC_           "wfm" // Form object (dBASE Form Designer)
#define EXT_FIC_           "wfn" // Font (CorelDRAW)
#define EXT_FIC_           "wfx" // Data file (Winfax)
#define EXT_FIC_           "wg1" // Worksheet (Lotus 1-2-3/G)
#define EXT_FIC_           "wg2" // Worksheet (Lotus 1-2-3 for OS/2)
#define EXT_FIC_           "wid" // Width table (Ventura Publisher)
#define EXT_FIC_           "win" // Window file (FoxPro - dBASE)

#define EXT_FIC_           "wiz" // Page wizard (MS Publisher)
#define EXT_FIC_           "wjp" // WildTangent Branded .jpg file
#define EXT_FIC_           "wk1" // Spreadsheet (Lotus 1-2-3 version 2.x - Symphony 1.1+)
#define EXT_FIC_           "wk3" // Spreadsheet (Lotus 1-2-3 version 3.x)
#define EXT_FIC_           "wk4" // Spreadsheet (Lotus 1-2-3 version 3.4)
#define EXT_FIC_           "wkb" // Document (WordPerfect for Win)

#define EXT_FIC_           "wke" // Spreatsheet (Lotus 1-2-3 educational version)
#define EXT_FIC_           "wkq" // Spreatsheet (Quattro)
#define EXT_FIC_           "wks" // Spreadsheet (Lotus 1-2-3 version 1A - Symphony 1.0 - MS Works)

#define EXT_FIC_           "wll" // Word Add-in
#define EXT_FIC_           "wlk" // Graphics (Virtus Walkthrough)
#define EXT_FIC_           "wlt" // eWallet file


#define EXT_FIC_           "wma" // Microsoft Active Streaming file
#define EXT_FIC_           "wmc" // Backup of startup files by Windows MathCad autoexec.wmc


#define EXT_FIC_           "wmf" // Windows MetaFile vector graphics
#define EXT_FIC_           "wml" // Wireless markup language
#define EXT_FIC_           "wmv" // MS Active Streaming file
#define EXT_FIC_           "wmz" // Windows Media Compressed skin file
#define EXT_FIC_           "wn" //  Text (NeXT WriteNow)
#define EXT_FIC_           "wnf" // Outline font description (CorelDRAW native format)
#define EXT_FIC_           "wo4" // STABCAL file
#define EXT_FIC_           "wo7" // STABCAL file
#define EXT_FIC_           "woa" // Swap file (Windows 3.x)
#define EXT_FIC_           "woc" // Organization (Windows OrgChart)
#define EXT_FIC_           "wor" // MapInfo Workspace
#define EXT_FIC_           "wot" // WebEx Saved Meeting Movie
#define EXT_FIC_           "wow" // Music (8 channels) (Grave Mod Player)
#define EXT_FIC_           "wp" //  Text file (WordPerfect 4.2)
#define EXT_FIC_           "wp5" // Document (WordPerfect 5.x)
#define EXT_FIC_           "wpd" // Document (WordPerfect 6.0 - PFS:WindowWorks)
#define EXT_FIC_           "wpf" // Fax (WorldPort)

#define EXT_FIC_           "wpg" // WildTangent Branded .PNG file

#define EXT_FIC_           "wpj" // MS Works Projects
#define EXT_FIC_           "wpk" // Macros (WordPerfect for Win)
#define EXT_FIC_           "wpl" // Draxy Software Wallpaper Sequencer

#define EXT_FIC_           "wpm" // Macros (WordPerfect)
#define EXT_FIC_           "wps" // Text document (MS Works)
#define EXT_FIC_           "wpt" // WordPerfect template

#define EXT_FIC_           "wpw" // PerfectWorks document
#define EXT_FIC_           "wq!" // Compressed spreadsheet (Quattro Pro)
#define EXT_FIC_           "wq1" // Spreadsheet (Quattro Pro)
#define EXT_FIC_           "wr1" // Spreadsheet (Symphony 1.1 - 1.2 - 2)
#define EXT_FIC_           "wrd" // Template (Charisma)
#define EXT_FIC_           "wri" // Text file (Windows Write)
#define EXT_FIC_           "wrk" // Spreadsheet (Symphony 1.0, 1.2, 2.0, 3.0)
#define EXT_FIC_           "wrl" // Plain text VRML file
#define EXT_FIC_           "wrml" // Plain text VRML file
#define EXT_FIC_           "wrp" // Compressed Amiga file archive created by WARP
#define EXT_FIC_           "wrs" // Windows Resource eg. printer driver (WordPerfect for Win)
#define EXT_FIC_           "ws" //  Text file (WordStar 5.0-6.0)
#define EXT_FIC_           "ws2" // Text file (WordStar 2000)
#define EXT_FIC_           "wsc" // Windows scripting component file
#define EXT_FIC_           "wsd" // Document (WordStar)
#define EXT_FIC_           "wsh" // Windows Script Host Settings file
#define EXT_FIC_           "wsp" // Workspace (Fortran PowerStation)
#define EXT_FIC_           "wsr" // FirstStop WebSearch file
#define EXT_FIC_           "wst" // Text file (WordStar)
#define EXT_FIC_           "wsx" // WinMX Filesharing Program
#define EXT_FIC_           "wsz" // Skin Zip file (WinAmp)
#define EXT_FIC_           "wtr" // MS Encarta file
#define EXT_FIC_           "wve" // Component of a DIVX Movie Conversion

#define EXT_FIC_           "wvx" // Metafile
#define EXT_FIC_           "wvw" // Backup Wonderware InTouch window file
#define EXT_FIC_           "wwb" // Button bar for document window (WordPerfect for Win)
#define EXT_FIC_           "wwk" // Keyboard layout (WordPerfect for Win)
#define EXT_FIC_           "wwp" // Worms World Party Teams file
#define EXT_FIC_           "wws" // AutoRoute User Information
#define EXT_FIC_           "wwv" // WildTangent Branded .WAV file
#define EXT_FIC_           "wxp" // Document (EXP for Windows)
#define EXT_FIC_           "wxs" // Easy Cross crosstitch file
#define EXT_FIC_           "wzg" // WZebra file 
#define EXT_FIC_           "wzs" // Microsoft Word wizard 
#define EXT_FIC_           "x" //   Avs X image file (SDSC Image Tool)

#define EXT_FIC_           "x01" // Secondary index (Paradox)
#define EXT_FIC_           "x02" // Secondary index (Paradox)
#define EXT_FIC_           "x03" // Secondary index (Paradox)
#define EXT_FIC_           "x04" // Secondary index (Paradox)
#define EXT_FIC_           "x05" // Secondary index (Paradox)
#define EXT_FIC_           "x06" // Secondary index (Paradox)
#define EXT_FIC_           "x07" // Secondary index (Paradox)
#define EXT_FIC_           "x08" // Secondary index (Paradox)
#define EXT_FIC_           "x09" // Secondary index (Paradox)
#define EXT_FIC_           "x16" // Macromedia Program Extension (16-bit)
#define EXT_FIC_           "x32" // Macromedia Program Extension (32-bit)
#define EXT_FIC_           "xbm" // X11 Bitmap graphics
#define EXT_FIC_           "xdf" // Milnta APL Transfer Function

#define EXT_FIC_           "xfd" // XML Form in XFDL Format
#define EXT_FIC_           "xfn" // Printer font (Xerox 4045) (Ventura Publisher)
#define EXT_FIC_           "xft" // 24 pin printer font (ChiWriter)
#define EXT_FIC_           "xfx" // Fax File (various)
#define EXT_FIC_           "xi" //  Fast Tracker 2 Instrument or ScreamTracker Instrument File
#define EXT_FIC_           "xif" // Wang image file
#define EXT_FIC_           "xla" // Xlib Archive (xlibpas2.zip)
#define EXT_FIC_           "xla" // Add-in macro sheet (MS Excel)
#define EXT_FIC_           "xlb" // Data (MS Excel)
#define EXT_FIC_           "xlc" // Chart document (MS Excel)
#define EXT_FIC_           "xlk" // Excel Backup
#define EXT_FIC_           "xll" // Excel Dynamic Link Library (MS Excel)
#define EXT_FIC_           "xlm" // Macro sheet (MS Excel)
#define EXT_FIC_           "xlr" // MS Works file
#define EXT_FIC_           "xls" // Spreadsheet(MS Works)


#define EXT_FIC_           "xlt" // Template (MS Excel)

#define EXT_FIC_           "xlw" // Workbook (MS Excel)
#define EXT_FIC_           "xlx" // XoloX Incomplete Download file
#define EXT_FIC_           "xm" //  Music (Fast Tracker)
#define EXT_FIC_           "xmi" // Compressed eXtended MIdi music
#define EXT_FIC_           "xnf" // Standard Network File form
#define EXT_FIC_           "xnk" // Microsoft Exchange Shortcut
#define EXT_FIC_           "xpl" // Music file
#define EXT_FIC_           "xpm" // X11 Pixel Map graphics
#define EXT_FIC_           "xpr" // Memorex CD-ROM label file
#define EXT_FIC_           "xpt" // XPCOM Type Library
#define EXT_FIC_           "xpw" // Leading Market Technologies EXPO

#define EXT_FIC_           "xqt" // Executable file (Waffle)
#define EXT_FIC_           "xqt" // Macro sheet (SuperCalc)
#define EXT_FIC_           "xrf" // Cross-reference file
#define EXT_FIC_           "xsd" // XML Schema file  
#define EXT_FIC_           "xsf" // Milnta APL Transfer Function
#define EXT_FIC_           "xsl" // Extensible Stylesheet Language file
#define EXT_FIC_           "xss" // Ability Office Spreadsheet
#define EXT_FIC_           "xtb" // External translation table (LocoScript)
#define EXT_FIC_           "xtr " // MapTool file (an add-on for UI-View)

#define EXT_FIC_           "xvb" // WinExplorer VB Script
#define EXT_FIC_           "xwd" // X Window System window dump image graphics (SDSC Image Tool)
#define EXT_FIC_           "xwk" // Keyboard mapping (Crosstalk)
#define EXT_FIC_           "xwp" // Session (Crosstalk)

#define EXT_FIC_           "xx" //  Compressed file ASCII archive created by XXENCODE (uuexe515.exe)
#define EXT_FIC_           "xxe" // Compressed file ASCII archive created by XXENCODE (uuexe515.exe)
#define EXT_FIC_           "xxx" // Singer Sewing Machine Professional SewWare file

#define EXT_FIC_           "xy" //  Text file (XY Write)
#define EXT_FIC_           "xy3" // Text file (XYWrite III)
#define EXT_FIC_           "xyw" // Text file (XyWrite III)
#define EXT_FIC_           "xyz" // ASCII RPG Maker Graphic Format

#define EXT_FIC_           "y" //   Yacc grammar file

#define EXT_FIC_           "y01" // Secondary index (Paradox)
#define EXT_FIC_           "y02" // Secondary index (Paradox)
#define EXT_FIC_           "y03" // Secondary index (Paradox)
#define EXT_FIC_           "y04" // Secondary index (Paradox)
#define EXT_FIC_           "y05" // Secondary index (Paradox)
#define EXT_FIC_           "y06" // Secondary index (Paradox)
#define EXT_FIC_           "y07" // Secondary index (Paradox)
#define EXT_FIC_           "y08" // Secondary index (Paradox)
#define EXT_FIC_           "y09" // Secondary index (Paradox)
#define EXT_FIC_           "yal" // Data (Arts & Letters)
#define EXT_FIC_           "yuv" // Yuv graphics
#define EXT_FIC_           "yz" //  Compressed file archive created by YAC
#define EXT_FIC_           "z" // Compressed file ASCII archive created by COMPRESS (comp430d.zip)

#define EXT_FIC_           "z3" // Infocom game module
#define EXT_FIC_           "zap" // FileWrangler Compressed file

#define EXT_FIC_           "zbd" // Canon ZoomBrowser Database file


#define EXT_FIC_           "zdb" // Wonder Word data file
#define EXT_FIC_           "zdg" // Compressed ZiffNet text document (Zview)
#define EXT_FIC_           "zdp" // ZDNet Password Pro 32
#define EXT_FIC_           "zer" // Data file (Zerberus)
#define EXT_FIC_           "zfx" // ZFX - CC3 File Packer Tool
#define EXT_FIC_           "zgm" // Graphics (Zenographics)
#define EXT_FIC_           "zip" // Compressed file archive created by PKZIP (pkz204g.exe)
#define EXT_FIC_           "zl?" // Zone Alarm Mailsafe Renamed File.


#define EXT_FIC_           "zls" // Atlantis Ocean Mind Word Processing file
#define EXT_FIC_           "zom" // Compressed Amiga file archive created by ZOOM
#define EXT_FIC_           "zon" // Grand Theft Auto 3 Zone file
#define EXT_FIC_           "zoo" // Compressed file archive created by ZOO (zoo210.exe)
#define EXT_FIC_           "zst" // ZSNES Slot 0 Savestate
#define EXT_FIC_           "ztd" // Ziff Davis Media text database
#define EXT_FIC_           "zvd" // Zyxel Voicefile (Z-Fax)
#define EXT_FIC_           "zzt" // ZZT Game Creation System
#define EXT_FIC_           "~$~" // Temporary file (1st Reader)
#define EXT_FIC_           "~ap" // Old AppExpert project database (Borland C++ 4.5)
#define EXT_FIC_           "~de" // Project backup (Borland C++ 4.5)
#define EXT_FIC_           "~mn" // Menu backup (Norton Commander)
#define EXT_FIC_           "\201$\201" //   Temporary file (1st Reader)

*/

#define FORM_FIC( ext )		"%s.ext"


#endif
