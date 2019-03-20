#ifndef UI_CC_VIEW_H_
#define UI_CC_VIEW_H_

#include <cstddef>
#include <string>
#include <iostream>

namespace ui {

class View {
	public:
		View();
		~View();
		void Clear();
		void ShowTitle();
		void ShowMessage(std::string str );
		void ShowMainMenu();
		void ShowFileMenu();
		void ShowDictionaryMenu();
		void ShowEntityMenu();
		void ShowAttributeMenu();
};


}  // end namespace ui

#endif  // UI_CC_VIEW_H_