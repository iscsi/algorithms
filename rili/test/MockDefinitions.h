#pragma once
/** @file */

#include <functional>
#include <memory>
#include <rili/test/MakeUnique.h>
#include <rili/test/CallHandler.h>
#include <rili/test/Config.h>
#include <rili/test/ConvertToString.h>
#include <rili/test/EventHandler.h>
#include <string>
#include <utility>

/// @cond INTERNAL

namespace rili {
namespace test {
namespace mock {
template <typename T>
std::string wrapToString(T const& t) noexcept {
	return "{" + toString(t) + "}";
}

[[noreturn]] void onUnexpectedCall();
}  // namespace mock
}  // namespace test
}  // namespace rili
#define RILI_MOCK_VA_ARGS_MACRO_EXPAND(x) x

#define RILI_EXPECT_CALL_HELPER(FILE, LINE, OBJECT, METHOD_NAME, HANDLER, COMMENT, ...) \
	OBJECT.__##METHOD_NAME(HANDLER, FILE, std::to_string(LINE), COMMENT)

#define RILI_MOCK0_HELPER(FILE, LINE, RESULT, NAME, SPECIFIERS, ...)												  \
	void __##NAME(std::function<RESULT()> f, std::string const& file, std::string const& line,						\
				  std::string const& comment) SPECIFIERS {															\
		rili::test::CallHandler::getInstance().registerCall(														  \
			this, #RESULT " " #NAME "() " #SPECIFIERS,																\
			std::unique_ptr<rili::test::UniversalCallbackHolder>(													 \
				rili::make_unique<rili::test::CallbackHolder<std::function<RESULT()>>>(f)),						   \
			file, line, comment);																					 \
	}																												 \
	RESULT NAME() SPECIFIERS override {																			   \
		auto callbackHolder =																						 \
			rili::test::CallHandler::getInstance().getCallbackHolder(this, #RESULT " " #NAME "() " #SPECIFIERS);	  \
		if (callbackHolder) {																						 \
			return (*static_cast<std::function<RESULT()> const*>(callbackHolder->getCallbackPointer()))();			\
		} else {																									  \
			rili::test::EventHandler::getInstance().unexpectedCall(FILE, std::to_string(LINE), this,				  \
																   #RESULT " " #NAME "() " #SPECIFIERS, "some args"); \
			rili::test::mock::onUnexpectedCall();																	 \
		}																											 \
	}

#define RILI_MOCK1_HELPER(FILE, LINE, RESULT, NAME, T1, SPECIFIERS, ...)									   \
	void __##NAME(std::function<RESULT(T1)> f, std::string const& file, std::string const& line,			   \
				  std::string const& comment) SPECIFIERS {													 \
		rili::test::CallHandler::getInstance().registerCall(												   \
			this, #RESULT " " #NAME "(" #T1 ") " #SPECIFIERS,												  \
			std::unique_ptr<rili::test::UniversalCallbackHolder>(											  \
				rili::make_unique<rili::test::CallbackHolder<std::function<RESULT(T1)>>>(f)),				  \
			file, line, comment);																			  \
	}																										  \
	RESULT NAME(T1 t1) SPECIFIERS override {																   \
		auto callbackHolder = rili::test::CallHandler::getInstance().getCallbackHolder(						\
			this, #RESULT " " #NAME "(" #T1 ") " #SPECIFIERS);												 \
		if (callbackHolder) {																				  \
			return (*static_cast<std::function<RESULT(T1)> const*>(callbackHolder->getCallbackPointer()))(	 \
				std::forward<T1>(t1));																		 \
		} else {																							   \
			rili::test::EventHandler::getInstance().unexpectedCall(FILE, std::to_string(LINE), this,		   \
																   #RESULT " " #NAME "(" #T1 ") " #SPECIFIERS, \
																   rili::test::mock::wrapToString(t1));		\
			rili::test::mock::onUnexpectedCall();															  \
		}																									  \
	}

#define RILI_MOCK2_HELPER(FILE, LINE, RESULT, NAME, T1, T2, SPECIFIERS, ...)								   \
	void __##NAME(std::function<RESULT(T1, T2)> f, std::string const& file, std::string const& line,		   \
				  std::string const& comment) SPECIFIERS {													 \
		rili::test::CallHandler::getInstance().registerCall(												   \
			this, #RESULT " " #NAME "(" #T1 ", " #T2 ") " #SPECIFIERS,										 \
			std::unique_ptr<rili::test::UniversalCallbackHolder>(											  \
				rili::make_unique<rili::test::CallbackHolder<std::function<RESULT(T1, T2)>>>(f)),			  \
			file, line, comment);																			  \
	}																										  \
	RESULT NAME(T1 t1, T2 t2) SPECIFIERS override {															\
		auto callbackHolder = rili::test::CallHandler::getInstance().getCallbackHolder(						\
			this, #RESULT " " #NAME "(" #T1 ", " #T2 ") " #SPECIFIERS);										\
		if (callbackHolder) {																				  \
			return (*static_cast<std::function<RESULT(T1, T2)> const*>(callbackHolder->getCallbackPointer()))( \
				std::forward<T1>(t1), std::forward<T2>(t2));												   \
		} else {																							   \
			rili::test::EventHandler::getInstance().unexpectedCall(											\
				FILE, std::to_string(LINE), this, #RESULT " " #NAME "(" #T1 ", " #T2 ") " #SPECIFIERS,		 \
				rili::test::mock::wrapToString(t1) + ", " + rili::test::mock::wrapToString(t2));			   \
			rili::test::mock::onUnexpectedCall();															  \
		}																									  \
	}

#define RILI_MOCK3_HELPER(FILE, LINE, RESULT, NAME, T1, T2, T3, SPECIFIERS, ...)								   \
	void __##NAME(std::function<RESULT(T1, T2, T3)> f, std::string const& file, std::string const& line,		   \
				  std::string const& comment) SPECIFIERS {														 \
		rili::test::CallHandler::getInstance().registerCall(													   \
			this, #RESULT " " #NAME "(" #T1 ", " #T2 ", " #T3 ") " #SPECIFIERS,									\
			std::unique_ptr<rili::test::UniversalCallbackHolder>(												  \
				rili::make_unique<rili::test::CallbackHolder<std::function<RESULT(T1, T2, T3)>>>(f)),			  \
			file, line, comment);																				  \
	}																											  \
	RESULT NAME(T1 t1, T2 t2, T3 t3) SPECIFIERS override {														 \
		auto callbackHolder = rili::test::CallHandler::getInstance().getCallbackHolder(							\
			this, #RESULT " " #NAME "(" #T1 ", " #T2 ", " #T3 ") " #SPECIFIERS);								   \
		if (callbackHolder) {																					  \
			return (*static_cast<std::function<RESULT(T1, T2, T3)> const*>(callbackHolder->getCallbackPointer()))( \
				std::forward<T1>(t1), std::forward<T2>(t2), std::forward<T3>(t3));								 \
		} else {																								   \
			rili::test::EventHandler::getInstance().unexpectedCall(												\
				FILE, std::to_string(LINE), this, #RESULT " " #NAME "(" #T1 ", " #T2 ", " #T3 ") " #SPECIFIERS,	\
				rili::test::mock::wrapToString(t1) + ", " + rili::test::mock::wrapToString(t2) + ", " +			\
					rili::test::mock::wrapToString(t3));														   \
			rili::test::mock::onUnexpectedCall();																  \
		}																										  \
	}

#define RILI_MOCK4_HELPER(FILE, LINE, RESULT, NAME, T1, T2, T3, T4, SPECIFIERS, ...)								   \
	void __##NAME(std::function<RESULT(T1, T2, T3, T4)> f, std::string const& file, std::string const& line,		   \
				  std::string const& comment) SPECIFIERS {															 \
		rili::test::CallHandler::getInstance().registerCall(														   \
			this, #RESULT " " #NAME "(" #T1 ", " #T2 ", " #T3 ", " #T4 ") " #SPECIFIERS,							   \
			std::unique_ptr<rili::test::UniversalCallbackHolder>(													  \
				rili::make_unique<rili::test::CallbackHolder<std::function<RESULT(T1, T2, T3, T4)>>>(f)),			  \
			file, line, comment);																					  \
	}																												  \
	RESULT NAME(T1 t1, T2 t2, T3 t3, T4 t4) SPECIFIERS override {													  \
		auto callbackHolder = rili::test::CallHandler::getInstance().getCallbackHolder(								\
			this, #RESULT " " #NAME "(" #T1 ", " #T2 ", " #T3 ", " #T4 ") " #SPECIFIERS);							  \
		if (callbackHolder) {																						  \
			return (*static_cast<std::function<RESULT(T1, T2, T3, T4)> const*>(callbackHolder->getCallbackPointer()))( \
				std::forward<T1>(t1), std::forward<T2>(t2), std::forward<T3>(t3), std::forward<T4>(t4));			   \
		} else {																									   \
			rili::test::EventHandler::getInstance().unexpectedCall(													\
				FILE, std::to_string(LINE), this,																	  \
				#RESULT " " #NAME "(" #T1 ", " #T2 ", " #T3 ", " #T4 ") " #SPECIFIERS,								 \
				rili::test::mock::wrapToString(t1) + ", " + rili::test::mock::wrapToString(t2) + ", " +				\
					rili::test::mock::wrapToString(t3) + ", " + rili::test::mock::wrapToString(t4));				   \
			rili::test::mock::onUnexpectedCall();																	  \
		}																											  \
	}

#define RILI_MOCK5_HELPER(FILE, LINE, RESULT, NAME, T1, T2, T3, T4, T5, SPECIFIERS, ...)							   \
	void __##NAME(std::function<RESULT(T1, T2, T3, T4, T5)> f, std::string const& file, std::string const& line,	   \
				  std::string const& comment) SPECIFIERS {															 \
		rili::test::CallHandler::getInstance().registerCall(														   \
			this, #RESULT " " #NAME "(" #T1 ", " #T2 ", " #T3 ", " #T4 ", " #T5 ") " #SPECIFIERS,					  \
			std::unique_ptr<rili::test::UniversalCallbackHolder>(													  \
				rili::make_unique<rili::test::CallbackHolder<std::function<RESULT(T1, T2, T3, T4, T5)>>>(f)),		  \
			file, line, comment);																					  \
	}																												  \
	RESULT NAME(T1 t1, T2 t2, T3 t3, T4 t4, T5 t5) SPECIFIERS override {											   \
		auto callbackHolder = rili::test::CallHandler::getInstance().getCallbackHolder(								\
			this, #RESULT " " #NAME "(" #T1 ", " #T2 ", " #T3 ", " #T4 ", " #T5 ") " #SPECIFIERS);					 \
		if (callbackHolder) {																						  \
			return (																								   \
				*static_cast<std::function<RESULT(T1, T2, T3, T4, T5)> const*>(callbackHolder->getCallbackPointer()))( \
				std::forward<T1>(t1), std::forward<T2>(t2), std::forward<T3>(t3), std::forward<T4>(t4),				\
				std::forward<T5>(t5));																				 \
		} else {																									   \
			rili::test::EventHandler::getInstance().unexpectedCall(													\
				FILE, std::to_string(LINE), this,																	  \
				#RESULT " " #NAME "(" #T1 ", " #T2 ", " #T3 ", " #T4 ", " #T5 ") " #SPECIFIERS,						\
				rili::test::mock::wrapToString(t1) + ", " + rili::test::mock::wrapToString(t2) + ", " +				\
					rili::test::mock::wrapToString(t3) + ", " + rili::test::mock::wrapToString(t4) + ", " +			\
					rili::test::mock::wrapToString(t5));															   \
			rili::test::mock::onUnexpectedCall();																	  \
		}																											  \
	}

#define RILI_MOCK6_HELPER(FILE, LINE, RESULT, NAME, T1, T2, T3, T4, T5, T6, SPECIFIERS, ...)						 \
	void __##NAME(std::function<RESULT(T1, T2, T3, T4, T5, T6)> f, std::string const& file, std::string const& line, \
				  std::string const& comment) SPECIFIERS {														   \
		rili::test::CallHandler::getInstance().registerCall(														 \
			this, #RESULT " " #NAME "(" #T1 ", " #T2 ", " #T3 ", " #T4 ", " #T5 ", " #T6 ") " #SPECIFIERS,		   \
			std::unique_ptr<rili::test::UniversalCallbackHolder>(													\
				rili::make_unique<rili::test::CallbackHolder<std::function<RESULT(T1, T2, T3, T4, T5, T6)>>>(f)),	\
			file, line, comment);																					\
	}																												\
	RESULT NAME(T1 t1, T2 t2, T3 t3, T4 t4, T5 t5, T6 t6) SPECIFIERS override {									  \
		auto callbackHolder = rili::test::CallHandler::getInstance().getCallbackHolder(							  \
			this, #RESULT " " #NAME "(" #T1 ", " #T2 ", " #T3 ", " #T4 ", " #T5 ", " #T6 ") " #SPECIFIERS);		  \
		if (callbackHolder) {																						\
			return (*static_cast<std::function<RESULT(T1, T2, T3, T4, T5, T6)> const*>(							  \
				callbackHolder->getCallbackPointer()))(std::forward<T1>(t1), std::forward<T2>(t2),				   \
													   std::forward<T3>(t3), std::forward<T4>(t4),				   \
													   std::forward<T5>(t5), std::forward<T6>(t6));				  \
		} else {																									 \
			rili::test::EventHandler::getInstance().unexpectedCall(												  \
				FILE, std::to_string(LINE), this,																	\
				#RESULT " " #NAME "(" #T1 ", " #T2 ", " #T3 ", " #T4 ", " #T5 ", " #T6 ") " #SPECIFIERS,			 \
				rili::test::mock::wrapToString(t1) + ", " + rili::test::mock::wrapToString(t2) + ", " +			  \
					rili::test::mock::wrapToString(t3) + ", " + rili::test::mock::wrapToString(t4) + ", " +		  \
					rili::test::mock::wrapToString(t5) + ", " + rili::test::mock::wrapToString(t6));				 \
			rili::test::mock::onUnexpectedCall();																	\
		}																											\
	}

#define RILI_MOCK7_HELPER(FILE, LINE, RESULT, NAME, T1, T2, T3, T4, T5, T6, T7, SPECIFIERS, ...)					  \
	void __##NAME(std::function<RESULT(T1, T2, T3, T4, T5, T6, T7)> f, std::string const& file,					   \
				  std::string const& line, std::string const& comment) SPECIFIERS {								   \
		rili::test::CallHandler::getInstance().registerCall(														  \
			this, #RESULT " " #NAME "(" #T1 ", " #T2 ", " #T3 ", " #T4 ", " #T5 ", " #T6 ", " #T7 ") " #SPECIFIERS,   \
			std::unique_ptr<rili::test::UniversalCallbackHolder>(													 \
				rili::make_unique<rili::test::CallbackHolder<std::function<RESULT(T1, T2, T3, T4, T5, T6, T7)>>>(f)), \
			file, line, comment);																					 \
	}																												 \
	RESULT NAME(T1 t1, T2 t2, T3 t3, T4 t4, T5 t5, T6 t6, T7 t7) SPECIFIERS override {								\
		auto callbackHolder = rili::test::CallHandler::getInstance().getCallbackHolder(							   \
			this, #RESULT " " #NAME "(" #T1 ", " #T2 ", " #T3 ", " #T4 ", " #T5 ", " #T6 ", " #T7 ") " #SPECIFIERS);  \
		if (callbackHolder) {																						 \
			return (*static_cast<std::function<RESULT(T1, T2, T3, T4, T5, T6, T7)> const*>(						   \
				callbackHolder->getCallbackPointer()))(															   \
				std::forward<T1>(t1), std::forward<T2>(t2), std::forward<T3>(t3), std::forward<T4>(t4),			   \
				std::forward<T5>(t5), std::forward<T6>(t6), std::forward<T7>(t7));									\
		} else {																									  \
			rili::test::EventHandler::getInstance().unexpectedCall(												   \
				FILE, std::to_string(LINE), this,																	 \
				#RESULT " " #NAME "(" #T1 ", " #T2 ", " #T3 ", " #T4 ", " #T5 ", " #T6 ", " #T7 ") " #SPECIFIERS,	 \
				rili::test::mock::wrapToString(t1) + ", " + rili::test::mock::wrapToString(t2) + ", " +			   \
					rili::test::mock::wrapToString(t3) + ", " + rili::test::mock::wrapToString(t4) + ", " +		   \
					rili::test::mock::wrapToString(t5) + ", " + rili::test::mock::wrapToString(t6) + ", " +		   \
					rili::test::mock::wrapToString(t7));															  \
			rili::test::mock::onUnexpectedCall();																	 \
		}																											 \
	}

#define RILI_MOCK8_HELPER(FILE, LINE, RESULT, NAME, T1, T2, T3, T4, T5, T6, T7, T8, SPECIFIERS, ...)				   \
	void __##NAME(std::function<RESULT(T1, T2, T3, T4, T5, T6, T7, T8)> f, std::string const& file,					\
				  std::string const& line, std::string const& comment) SPECIFIERS {									\
		rili::test::CallHandler::getInstance().registerCall(														   \
			this,																									  \
			#RESULT " " #NAME "(" #T1 ", " #T2 ", " #T3 ", " #T4 ", " #T5 ", " #T6 ", " #T7 ", " #T8 ") " #SPECIFIERS, \
			std::unique_ptr<rili::test::UniversalCallbackHolder>(													  \
				rili::make_unique<rili::test::CallbackHolder<std::function<RESULT(T1, T2, T3, T4, T5, T6, T7, T8)>>>(  \
					f)),																							   \
			file, line, comment);																					  \
	}																												  \
	RESULT NAME(T1 t1, T2 t2, T3 t3, T4 t4, T5 t5, T6 t6, T7 t7, T8 t8) SPECIFIERS override {						  \
		auto callbackHolder = rili::test::CallHandler::getInstance().getCallbackHolder(								\
			this, #RESULT " " #NAME "(" #T1 ", " #T2 ", " #T3 ", " #T4 ", " #T5 ", " #T6 ", " #T7 ", " #T8			 \
						  ") " #SPECIFIERS);																		   \
		if (callbackHolder) {																						  \
			return (*static_cast<std::function<RESULT(T1, T2, T3, T4, T5, T6, T7, T8)> const*>(						\
				callbackHolder->getCallbackPointer()))(																\
				std::forward<T1>(t1), std::forward<T2>(t2), std::forward<T3>(t3), std::forward<T4>(t4),				\
				std::forward<T5>(t5), std::forward<T6>(t6), std::forward<T7>(t7), std::forward<T8>(t8));			   \
		} else {																									   \
			rili::test::EventHandler::getInstance().unexpectedCall(													\
				FILE, std::to_string(LINE), this, #RESULT " " #NAME "(" #T1 ", " #T2 ", " #T3 ", " #T4 ", " #T5		\
														  ", " #T6 ", " #T7 ", " #T8 ") " #SPECIFIERS,				 \
				rili::test::mock::wrapToString(t1) + ", " + rili::test::mock::wrapToString(t2) + ", " +				\
					rili::test::mock::wrapToString(t3) + ", " + rili::test::mock::wrapToString(t4) + ", " +			\
					rili::test::mock::wrapToString(t5) + ", " + rili::test::mock::wrapToString(t6) + ", " +			\
					rili::test::mock::wrapToString(t7) + ", " + rili::test::mock::wrapToString(t8));				   \
			rili::test::mock::onUnexpectedCall();																	  \
		}																											  \
	}

#define RILI_MOCK9_HELPER(FILE, LINE, RESULT, NAME, T1, T2, T3, T4, T5, T6, T7, T8, T9, SPECIFIERS, ...)			\
	void __##NAME(std::function<RESULT(T1, T2, T3, T4, T5, T6, T7, T8, T9)> f, std::string const& file,			 \
				  std::string const& line, std::string const& comment) SPECIFIERS {								 \
		rili::test::CallHandler::getInstance().registerCall(														\
			this, #RESULT " " #NAME "(" #T1 ", " #T2 ", " #T3 ", " #T4 ", " #T5 ", " #T6 ", " #T7 ", " #T8 ", " #T9 \
						  ") " #SPECIFIERS,																		 \
			std::unique_ptr<rili::test::UniversalCallbackHolder>(												   \
				rili::make_unique<																				  \
					rili::test::CallbackHolder<std::function<RESULT(T1, T2, T3, T4, T5, T6, T7, T8, T9)>>>(f)),	 \
			file, line, comment);																				   \
	}																											   \
	RESULT NAME(T1 t1, T2 t2, T3 t3, T4 t4, T5 t5, T6 t6, T7 t7, T8 t8, T9 t9) SPECIFIERS override {				\
		auto callbackHolder = rili::test::CallHandler::getInstance().getCallbackHolder(							 \
			this, #RESULT " " #NAME "(" #T1 ", " #T2 ", " #T3 ", " #T4 ", " #T5 ", " #T6 ", " #T7 ", " #T8 ", " #T9 \
						  ") " #SPECIFIERS);																		\
		if (callbackHolder) {																					   \
			return (*static_cast<std::function<RESULT(T1, T2, T3, T4, T5, T6, T7, T8, T9)> const*>(				 \
				callbackHolder->getCallbackPointer()))(															 \
				std::forward<T1>(t1), std::forward<T2>(t2), std::forward<T3>(t3), std::forward<T4>(t4),			 \
				std::forward<T5>(t5), std::forward<T6>(t6), std::forward<T7>(t7), std::forward<T8>(t8),			 \
				std::forward<T9>(t9));																			  \
		} else {																									\
			rili::test::EventHandler::getInstance().unexpectedCall(												 \
				FILE, std::to_string(LINE), this, #RESULT " " #NAME "(" #T1 ", " #T2 ", " #T3 ", " #T4 ", " #T5	 \
														  ", " #T6 ", " #T7 ", " #T8 ", " #T9 ") " #SPECIFIERS,	 \
				rili::test::mock::wrapToString(t1) + ", " + rili::test::mock::wrapToString(t2) + ", " +			 \
					rili::test::mock::wrapToString(t3) + ", " + rili::test::mock::wrapToString(t4) + ", " +		 \
					rili::test::mock::wrapToString(t5) + ", " + rili::test::mock::wrapToString(t6) + ", " +		 \
					rili::test::mock::wrapToString(t7) + ", " + rili::test::mock::wrapToString(t8) + ", " +		 \
					rili::test::mock::wrapToString(t9));															\
			rili::test::mock::onUnexpectedCall();																   \
		}																										   \
	}

#define RILI_MOCK10_HELPER(FILE, LINE, RESULT, NAME, T1, T2, T3, T4, T5, T6, T7, T8, T9, T10, SPECIFIERS, ...)	   \
	void __##NAME(std::function<RESULT(T1, T2, T3, T4, T5, T6, T7, T8, T9, T10)> f, std::string const& file,		 \
				  std::string const& line, std::string const& comment) SPECIFIERS {								  \
		rili::test::CallHandler::getInstance().registerCall(														 \
			this, #RESULT " " #NAME "(" #T1 ", " #T2 ", " #T3 ", " #T4 ", " #T5 ", " #T6 ", " #T7 ", " #T8 ", " #T9  \
						  ", " #T10 ") " #SPECIFIERS,																\
			std::unique_ptr<rili::test::UniversalCallbackHolder>(													\
				rili::make_unique<																				   \
					rili::test::CallbackHolder<std::function<RESULT(T1, T2, T3, T4, T5, T6, T7, T8, T9, T10)>>>(f)), \
			file, line, comment);																					\
	}																												\
	RESULT NAME(T1 t1, T2 t2, T3 t3, T4 t4, T5 t5, T6 t6, T7 t7, T8 t8, T9 t9, T10 t10) SPECIFIERS override {		\
		auto callbackHolder = rili::test::CallHandler::getInstance().getCallbackHolder(							  \
			this, #RESULT " " #NAME "(" #T1 ", " #T2 ", " #T3 ", " #T4 ", " #T5 ", " #T6 ", " #T7 ", " #T8 ", " #T9  \
						  ", " #T10 ") " #SPECIFIERS);															   \
		if (callbackHolder) {																						\
			return (*static_cast<std::function<RESULT(T1, T2, T3, T4, T5, T6, T7, T8, T9, T10)> const*>(			 \
				callbackHolder->getCallbackPointer()))(															  \
				std::forward<T1>(t1), std::forward<T2>(t2), std::forward<T3>(t3), std::forward<T4>(t4),			  \
				std::forward<T5>(t5), std::forward<T6>(t6), std::forward<T7>(t7), std::forward<T8>(t8),			  \
				std::forward<T9>(t9), std::forward<T10>(t10));													   \
		} else {																									 \
			rili::test::EventHandler::getInstance().unexpectedCall(												  \
				FILE, std::to_string(LINE), this,																	\
				#RESULT " " #NAME "(" #T1 ", " #T2 ", " #T3 ", " #T4 ", " #T5 ", " #T6 ", " #T7 ", " #T8 ", " #T9	\
						", " #T10 ") " #SPECIFIERS,																  \
				rili::test::mock::wrapToString(t1) + ", " + rili::test::mock::wrapToString(t2) + ", " +			  \
					rili::test::mock::wrapToString(t3) + ", " + rili::test::mock::wrapToString(t4) + ", " +		  \
					rili::test::mock::wrapToString(t5) + ", " + rili::test::mock::wrapToString(t6) + ", " +		  \
					rili::test::mock::wrapToString(t7) + ", " + rili::test::mock::wrapToString(t8) + ", " +		  \
					rili::test::mock::wrapToString(t9) + ", " + rili::test::mock::wrapToString(t10));				\
			rili::test::mock::onUnexpectedCall();																	\
		}																											\
	}

/// @endcond INTERNAL

/**
 * @brief EXPECT_CALL(OBJECT, METHOD_NAME, MESSAGE) indicate that there is expected call of METHOD_NAME on object OBJECT
 *
 * If expectation will be not fullfited produce failure event, which contain:
 * * file location
 * * line number
 * * pointer to OBJECT,
 * * METHOD_NAME signature as string
 * * optional MESSAGE
 *
 * @note message parameter is optional - if not provided empty will be used
 */
#define EXPECT_CALL(OBJECT, METHOD_NAME, ...) \
	RILI_MOCK_VA_ARGS_MACRO_EXPAND(		   \
		RILI_EXPECT_CALL_HELPER(__FILE__, __LINE__, OBJECT, METHOD_NAME, __VA_ARGS__, std::string(), std::string()))

/**
 * @brief MOCK0(RESULT, METHOD_NAME, SPECIFIERS) generate mocked method which returns RESULT type, take 0 arguments,
 * have name METHOD_NAME and optional SPECIFIERS (like "noexcept", "const" etc... )
 *
 * In case of unexpected call will be  produced failure event, which contain:
 * * file location
 * * line number
 * * pointer to OBJECT on which mocked method was called,
 * * METHOD_NAME signature includeing optional SPECIFIERS and RESULT type
 *
 * @note SPECIFIERS parameter is optional, however important if you would like to mock "const" or "noexcept" method.
 */
#define MOCK0(RESULT, ...) \
	RILI_MOCK_VA_ARGS_MACRO_EXPAND(RILI_MOCK0_HELPER(__FILE__, __LINE__, RESULT, __VA_ARGS__, , ))  // NOLINT

/**
 * @brief MOCK1(RESULT, METHOD_NAME, T1, SPECIFIERS) generate mocked method which returns RESULT type, take 1 argument
 * of type T1, have name METHOD_NAME and optional SPECIFIERS (like "noexcept", "const" etc...)
 *
 * In case of unexpected call will be  produced failure event, which contain:
 * * file location
 * * line number
 * * pointer to OBJECT on which mocked method was called,
 * * stringified argument (if T1 is streamable)
 * * METHOD_NAME signature includeing optional SPECIFIERS and RESULT type
 *
 * @note SPECIFIERS parameter is optional, however important if you would like to mock "const" or "noexcept" method.
 */
#define MOCK1(RESULT, METHOD_NAME, ...) \
	RILI_MOCK_VA_ARGS_MACRO_EXPAND(	 \
		RILI_MOCK1_HELPER(__FILE__, __LINE__, RESULT, METHOD_NAME, __VA_ARGS__, , ))  // NOLINT

/**
 * @brief MOCK2(RESULT, METHOD_NAME, T1, T2, SPECIFIERS) generate mocked method which returns RESULT type, take 2
 * arguments of types T1, T2, have name METHOD_NAME and optional SPECIFIERS (like "noexcept", "const" etc... )
 *
 * In case of unexpected call will be  produced failure event, which contain:
 * * file location
 * * line number
 * * pointer to OBJECT on which mocked method was called,
 * * stringified arguments (if T1, T2 are streamable)
 * * METHOD_NAME signature includeing optional SPECIFIERS and RESULT type
 *
 * @note SPECIFIERS parameter is optional, however important if you would like to mock "const" or "noexcept" method.
 */
#define MOCK2(RESULT, METHOD_NAME, T1, ...) \
	RILI_MOCK_VA_ARGS_MACRO_EXPAND(		 \
		RILI_MOCK2_HELPER(__FILE__, __LINE__, RESULT, METHOD_NAME, T1, __VA_ARGS__, , ))  // NOLINT

/**
 * @brief MOCK3(RESULT, METHOD_NAME, T1, T2, T3, SPECIFIERS) generate mocked method which returns RESULT type, take 3
 * arguments of types T1, T2, T3, have name METHOD_NAME and optional SPECIFIERS (like "noexcept", "const" etc... )
 *
 * In case of unexpected call will be  produced failure event, which contain:
 * * file location
 * * line number
 * * pointer to OBJECT on which mocked method was called,
 * * stringified arguments (if T1, T2, T3 are streamable)
 * * METHOD_NAME signature includeing optional SPECIFIERS and RESULT type
 *
 * @note SPECIFIERS parameter is optional, however important if you would like to mock "const" or "noexcept" method.
 */
#define MOCK3(RESULT, METHOD_NAME, T1, T2, ...) \
	RILI_MOCK_VA_ARGS_MACRO_EXPAND(			 \
		RILI_MOCK3_HELPER(__FILE__, __LINE__, RESULT, METHOD_NAME, T1, T2, __VA_ARGS__, , ))  // NOLINT

/**
 * @brief MOCK4(RESULT, METHOD_NAME, T1, T2, T3, T4, SPECIFIERS) generate mocked method which returns RESULT type, take
 * 4
 * arguments of types T1, T2, T3, T4, have name METHOD_NAME and optional SPECIFIERS (like "noexcept", "const" etc...)
 *
 * In case of unexpected call will be  produced failure event, which contain:
 * * file location
 * * line number
 * * pointer to OBJECT on which mocked method was called,
 * * stringified arguments (if T1, T2, T3, T4 are streamable)
 * * METHOD_NAME signature includeing optional SPECIFIERS and RESULT type
 *
 * @note SPECIFIERS parameter is optional, however important if you would like to mock "const" or "noexcept" method.
 */
#define MOCK4(RESULT, METHOD_NAME, T1, T2, T3, ...) \
	RILI_MOCK_VA_ARGS_MACRO_EXPAND(				 \
		RILI_MOCK4_HELPER(__FILE__, __LINE__, RESULT, METHOD_NAME, T1, T2, T3, __VA_ARGS__, , ))  // NOLINT

/**
 * @brief MOCK5(RESULT, METHOD_NAME, T1, T2, T3, T4, T5, SPECIFIERS) generate mocked method which returns RESULT type,
 * take 5 arguments of types T1, T2, T3, T4, T5, have name METHOD_NAME and optional SPECIFIERS (like "noexcept", "const"
 * etc...)
 *
 * In case of unexpected call will be  produced failure event, which contain:
 * * file location
 * * line number
 * * pointer to OBJECT on which mocked method was called,
 * * stringified arguments (if T1, T2, T3, T4, T5 are streamable)
 * * METHOD_NAME signature includeing optional SPECIFIERS and RESULT type
 *
 * @note SPECIFIERS parameter is optional, however important if you would like to mock "const" or "noexcept" method.
 */
#define MOCK5(RESULT, METHOD_NAME, T1, T2, T3, T4, ...) \
	RILI_MOCK_VA_ARGS_MACRO_EXPAND(					 \
		RILI_MOCK5_HELPER(__FILE__, __LINE__, RESULT, METHOD_NAME, T1, T2, T3, T4, __VA_ARGS__, , ))  // NOLINT

/**
 * @brief MOCK6(RESULT, METHOD_NAME, T1, T2, T3, T4, T5, T6, SPECIFIERS) generate mocked method which returns RESULT
 * type, take 6 arguments of types T1, T2, T3, T4, T5, T6, have name METHOD_NAME and optional SPECIFIERS (like
 * "noexcept", "const" etc...)
 *
 * In case of unexpected call will be  produced failure event, which contain:
 * * file location
 * * line number
 * * pointer to OBJECT on which mocked method was called,
 * * stringified arguments (if T1, T2, T3, T4, T5, T6 are streamable)
 * * METHOD_NAME signature includeing optional SPECIFIERS and RESULT type
 *
 * @note SPECIFIERS parameter is optional, however important if you would like to mock "const" or "noexcept" method.
 */
#define MOCK6(RESULT, METHOD_NAME, T1, T2, T3, T4, T5, ...) \
	RILI_MOCK_VA_ARGS_MACRO_EXPAND(						 \
		RILI_MOCK6_HELPER(__FILE__, __LINE__, RESULT, METHOD_NAME, T1, T2, T3, T4, T5, __VA_ARGS__, , ))  // NOLINT

/**
 * @brief MOCK7(RESULT, METHOD_NAME, T1, T2, T3, T4, T5, T6, T7, SPECIFIERS) generate mocked method which returns RESULT
 * type, take 7 arguments of types T1, T2, T3, T4, T5, T6, T7, have name METHOD_NAME and optional SPECIFIERS (like
 * "noexcept", "const" etc...)
 *
 * In case of unexpected call will be  produced failure event, which contain:
 * * file location
 * * line number
 * * pointer to OBJECT on which mocked method was called,
 * * stringified arguments (if T1, T2, T3, T4, T5, T6, T7 are streamable)
 * * METHOD_NAME signature includeing optional SPECIFIERS and RESULT type
 *
 * @note SPECIFIERS parameter is optional, however important if you would like to mock "const" or "noexcept" method.
 */
#define MOCK7(RESULT, METHOD_NAME, T1, T2, T3, T4, T5, T6, ...)													   \
	RILI_MOCK_VA_ARGS_MACRO_EXPAND(RILI_MOCK7_HELPER(__FILE__, __LINE__, RESULT, METHOD_NAME, T1, T2, T3, T4, T5, T6, \
													 __VA_ARGS__, , ))  // NOLINT

/**
 * @brief MOCK8(RESULT, METHOD_NAME, T1, T2, T3, T4, T5, T6, T7, T8, SPECIFIERS) generate mocked method which returns
 * RESULT type, take 8 arguments of types T1, T2, T3, T4, T5, T6, T7, T8, have name METHOD_NAME and optional SPECIFIERS
 * (like "noexcept", "const" etc...)
 *
 * In case of unexpected call will be  produced failure event, which contain:
 * * file location
 * * line number
 * * pointer to OBJECT on which mocked method was called,
 * * stringified arguments (if T1, T2, T3, T4, T5, T6, T7, T8 are streamable)
 * * METHOD_NAME signature includeing optional SPECIFIERS and RESULT type
 *
 * @note SPECIFIERS parameter is optional, however important if you would like to mock "const" or "noexcept" method.
 */
#define MOCK8(RESULT, METHOD_NAME, T1, T2, T3, T4, T5, T6, T7, ...)												   \
	RILI_MOCK_VA_ARGS_MACRO_EXPAND(RILI_MOCK8_HELPER(__FILE__, __LINE__, RESULT, METHOD_NAME, T1, T2, T3, T4, T5, T6, \
													 T7, __VA_ARGS__, , ))  // NOLINT

/**
 * @brief MOCK9(RESULT, METHOD_NAME, T1, T2, T3, T4, T5, T6, T7, T8, T9, SPECIFIERS) generate mocked method which
 * returns RESULT type, take 9  arguments of types T1, T2, T3, T4, T5, T6, T7, T8, T9, have name METHOD_NAME and
 * optional SPECIFIERS (like "noexcept", "const" etc... )
 *
 * In case of unexpected call will be  produced failure event, which contain:
 * * file location
 * * line number
 * * pointer to OBJECT on which mocked method was called,
 * * stringified arguments (if T1, T2, T3, T4, T5, T6, T7, T8, T9 are streamable)
 * * METHOD_NAME signature includeing optional SPECIFIERS and RESULT type
 *
 * @note SPECIFIERS parameter is optional, however important if you would like to mock "const" or "noexcept" method.
 */
#define MOCK9(RESULT, METHOD_NAME, T1, T2, T3, T4, T5, T6, T7, T8, ...)											   \
	RILI_MOCK_VA_ARGS_MACRO_EXPAND(RILI_MOCK9_HELPER(__FILE__, __LINE__, RESULT, METHOD_NAME, T1, T2, T3, T4, T5, T6, \
													 T7, T8, __VA_ARGS__, , ))  // NOLINT

/**
 * @brief MOCK10(RESULT, METHOD_NAME, T1, T2, T3, T4, T5, T6, T7, T8, T9, T10, SPECIFIERS) generate mocked method which
 * returns RESULT type, take 10 arguments of types T1, T2, T3, T4, T5, T6, T7, T8, T9, T10, have name METHOD_NAME and
 * optional SPECIFIERS (like "noexcept", "const" etc... )
 *
 * In case of unexpected call will be  produced failure event, which contain:
 * * file location
 * * line number
 * * pointer to OBJECT on which mocked method was called,
 * * stringified arguments (if T1, T2, T3, T4, T5, T6, T7, T8, T9, T10 are streamable)
 * * METHOD_NAME signature includeing optional SPECIFIERS and RESULT type
 *
 * @note SPECIFIERS parameter is optional, however important if you would like to mock "const" or "noexcept" method.
 */
#define MOCK10(RESULT, METHOD_NAME, T1, T2, T3, T4, T5, T6, T7, T8, T9, ...)										   \
	RILI_MOCK_VA_ARGS_MACRO_EXPAND(RILI_MOCK10_HELPER(__FILE__, __LINE__, RESULT, METHOD_NAME, T1, T2, T3, T4, T5, T6, \
													  T7, T8, T9, __VA_ARGS__, , ))  // NOLINT
