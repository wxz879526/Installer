//stamp:0000000000000001
/*<------------------------------------------------------------------------------------------------->*/
/*该文件由uiresbuilder生成，请不要手动修改*/
/*<------------------------------------------------------------------------------------------------->*/
#pragma once
#include <res.mgr/snamedvalue.h>
#define ROBJ_IN_CPP \
namespace SOUI \
{\
    const _R R;\
    const _UIRES UIRES;\
}
namespace SOUI
{
	class _UIRES{
		public:
		class _UIDEF{
			public:
			_UIDEF(){
				XML_INIT = _T("UIDEF:XML_INIT");
			}
			const TCHAR * XML_INIT;
		}UIDEF;
		class _LAYOUT{
			public:
			_LAYOUT(){
				XML_CUSTOM_MSG_BOX = _T("LAYOUT:XML_CUSTOM_MSG_BOX");
				XML_MAINWND = _T("LAYOUT:XML_MAINWND");
				XML_WELCOME = _T("LAYOUT:XML_WELCOME");
				XML_AGREEMENT = _T("LAYOUT:XML_AGREEMENT");
			}
			const TCHAR * XML_CUSTOM_MSG_BOX;
			const TCHAR * XML_MAINWND;
			const TCHAR * XML_WELCOME;
			const TCHAR * XML_AGREEMENT;
		}LAYOUT;
		class _values{
			public:
			_values(){
				string = _T("values:string");
				color = _T("values:color");
				skin = _T("values:skin");
			}
			const TCHAR * string;
			const TCHAR * color;
			const TCHAR * skin;
		}values;
		class _IMG{
			public:
			_IMG(){
				IMG_WND_BG = _T("IMG:IMG_WND_BG");
				welcome_center = _T("IMG:welcome_center");
				install = _T("IMG:install");
				custom_button = _T("IMG:custom_button");
				prog_bar = _T("IMG:prog_bar");
				prog_bkgnd = _T("IMG:prog_bkgnd");
			}
			const TCHAR * IMG_WND_BG;
			const TCHAR * welcome_center;
			const TCHAR * install;
			const TCHAR * custom_button;
			const TCHAR * prog_bar;
			const TCHAR * prog_bkgnd;
		}IMG;
		class _ICON{
			public:
			_ICON(){
				ICON_LOGO = _T("ICON:ICON_LOGO");
			}
			const TCHAR * ICON_LOGO;
		}ICON;
		class _SMENU{
			public:
			_SMENU(){
				menu_template = _T("SMENU:menu_template");
			}
			const TCHAR * menu_template;
		}SMENU;
		class _rtf{
			public:
			_rtf(){
				rtf_agreement = _T("rtf:rtf_agreement");
			}
			const TCHAR * rtf_agreement;
		}rtf;
	};
	const SNamedID::NAMEDVALUE namedXmlID[]={
		{L"_name_start",65535}		};
	class _R{
	public:
		class _name{
		public:
		_name(){
			_name_start = namedXmlID[0].strName;
		}
		 const wchar_t * _name_start;
		}name;

		class _id{
		public:
		const static int _name_start	=	65535;
		}id;

		class _string{
		public:
		}string;

		class _color{
		public:
		}color;

	};

#ifdef R_IN_CPP
	 extern const _R R;
	 extern const _UIRES UIRES;
#else
	 extern const __declspec(selectany) _R & R = _R();
	 extern const __declspec(selectany) _UIRES & UIRES = _UIRES();
#endif//R_IN_CPP
}
