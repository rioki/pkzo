// pkzo
// Copyright 2019 Sean Farrell <sean.farrell@rioki.org>

#ifndef _PKZO_DBG_H_
#define _PKZO_DBG_H_

#include <vector>
#include <string>
#include <sstream>
#include <winerror.h>

#include "defines.h"

#ifndef NDEBUG
/*!
 * Trace a message.
 *
 * In debug builds this mactor will write a message to trace buffer.
 *
 * @param SEV the error severity
 * @param MSG the message
 *
 * @{
 */
#define PKZO_TRACE(SEV, MSG) ::pkzo::trace(__FUNCTION__, SEV, MSG)
#define PKZO_TRACE_ERROR(MSG) PKZO_TRACE(::pkzo::TraceLevel::TRACE_ERROR, MSG)
#define PKZO_TRACE_WARNING(MSG) PKZO_TRACE(::pkzo::TraceLevel::TRACE_WARNING, MSG)
#define PKZO_TRACE_INFO(MSG) PKZO_TRACE(::pkzo::TraceLevel::TRACE_INFO, MSG)
/*! @} */

/*!
 * Throw an exception with callstack.
 *
 * In debug builds this macro will throw an exception with full callstack 
 * In release builds this macro will just throw the exception.
 *
 * @param EX the ection class to throw
 * @param MSG the message to set into the exception
 */
#define PKZO_THROW(EX, MSG) ::pkzo::throw_with_callstack<EX>(__FUNCTION__, MSG)

/*!
 * Asseert that throws an exception with callstack.
 *
 * In debug builds this macro will check the given condition and 
 * if the confition is false, throw an exception.
 * 
 * @param COND the confition to check
 */
#define PKZO_ASSERT(COND) if (static_cast<bool>(COND) == false) { ::pkzo::handle_assert(__FUNCTION__, #COND); }

/*!
 * Asseert that traces the error condition
 *
 * In debug builds this macro will check the given condition and 
 * if the confition is false, trace an error.
 * 
 * @param COND the confition to check
 */
#define PKZO_SOFT_ASSERT(COND) if (static_cast<bool>(COND) == false) { PKZO_TRACE_ERROR("Soft assert failed '" #COND "'."); }

#else
#define PKZO_TRACE(SEV, MSG) 
#define PKZO_TRACE_ERROR(MSG) 
#define PKZO_TRACE_WARNING(MSG) 
#define PKZO_TRACE_INFO(MSG)
#define PKZO_THROW(EX, MSG) throw EX(MSG)
#define PKZO_ASSERT(COND)
#define PKZO_SOFT_ASSERT(COND)
#endif

namespace pkzo
{
    /*!
     * Trace Level
     */
    enum class TraceLevel 
    {
        TRACE_ERROR,
        TRACE_WARNING,
        TRACE_INFO
    };

    /*!
     * Trace a message.
     *
     * This debug function will write a message to the trace buffer,
     * on windows this OutputDebugString. You should use DBG_TRACE macro 
     * instead of this function.
     * 
     * @param func the function that called the trace
     * @param lavel the trace level
     * @param msg the message to write
     *
     * @see PKZO_TRACE 
     */
    void trace(const std::string_view func, TraceLevel level, const std::string_view msg);

    /*!
     * Single entry in the callstack,
     */
    struct StackFrame
    {
        uint64_t address;       //!< function address
        std::string name;       //!< function name
        std::string module;     //!< module name
        unsigned int line;      //!< line of the function
        std::string file;       //!< file of the function
    };

    /*!
     * Pull call stack
     *
     * This debug utility function pulls a callstack. To pull a readable
     * callstack you need to have all PDBs next to the program.
     *
     * @return the callstack
     * 
     * @note This function is only available in debug builds.
     */
    PKZO_EXPORT
    std::vector<StackFrame> trace_stack();

    /*!
     * Handle asset failure.
     *
     * This debug utility function is used to throw an exception with call stack
     * if an assertion failed. You should use the DBG_ASSERT makro to use
     * this function.
     *
     * @param func the calling function
     * @param cond the assert condition as string
     *
     * @note This function is only available in debug builds.
     *
     * @see DBG_ASSERT
     */
    [[noreturn]] PKZO_EXPORT
    void handle_assert(const std::string_view func, const std::string_view cond);

    /*!
     * Throw exception with callstack.
     *
     * This debug utility function will pull a full callstack and append it to 
     * the given error message. You should use DBG_THROW macro instead of this 
     * function.
     *
     * @param func the calling function
     * @param msg the message to print
     *
     * @see PKZO_THROW 
     */
    template <typename Exception> [[noreturn]]
	void throw_with_callstack(const std::string_view func, const std::string_view msg) 
	{
		std::stringstream buff;
		buff << func << ": " << msg << "\n";
		buff << "\n";

		std::vector<StackFrame> stack = trace_stack();
		buff << "Callstack: \n";
		for (unsigned int i = 0; i < stack.size(); i++)
		{
			buff << "0x" << std::hex << stack[i].address << ": " << stack[i].name << "(" << std::dec << stack[i].line << ") in " << stack[i].module << "\n";
		}

		throw Exception(buff.str());
	}
}

#endif
