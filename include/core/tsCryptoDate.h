//	Copyright (c) 2018, TecSec, Inc.
//
//	Redistribution and use in source and binary forms, with or without
//	modification, are permitted provided that the following conditions are met:
//	
//		* Redistributions of source code must retain the above copyright
//		  notice, this list of conditions and the following disclaimer.
//		* Redistributions in binary form must reproduce the above copyright
//		  notice, this list of conditions and the following disclaimer in the
//		  documentation and/or other materials provided with the distribution.
//		* Neither the name of TecSec nor the names of the contributors may be
//		  used to endorse or promote products derived from this software 
//		  without specific prior written permission.
//		 
//	ALTERNATIVELY, provided that this notice is retained in full, this product
//	may be distributed under the terms of the GNU General Public License (GPL),
//	in which case the provisions of the GPL apply INSTEAD OF those given above.
//		 
//	THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS" AND
//	ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED
//	WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE
//	DISCLAIMED.  IN NO EVENT SHALL TECSEC BE LIABLE FOR ANY 
//	DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES
//	(INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES;
//	LOSS OF USE, DATA OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND
//	ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT
//	(INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS
//	SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
//
// Written by Roger Butler

/*! \file tsCryptoDate.h
 * <summary>Date conversion and manipulation class and functions</summary>
 */
 
 #ifndef __TSCRYPTODATE_H__
 #define __TSCRYPTODATE_H__
 			 
#pragma once

namespace tscrypto {
	////////////////////////////////////////////////////////////////////////////////////////////////////
	/// <summary>Converts a ZULU date into a TsDateStruct_t structure.</summary>
	///
	/// <param name="date">The zulu date.</param>
	/// <param name="tm">  [in,out] The TsDateStruct_t structure.</param>
	////////////////////////////////////////////////////////////////////////////////////////////////////
	VEILCORE_API void TSZuluStringToTM(const tsCryptoStringBase &date, TsDateStruct_t &tm);
	////////////////////////////////////////////////////////////////////////////////////////////////////
	/// <summary>Converts a TsDateStruct_t structure into a ZULU date</summary>
	///
	/// <param name="tm">  The TsDateStruct_t structure.</param>
	/// <param name="date">[in,out] The zulu date.</param>
	////////////////////////////////////////////////////////////////////////////////////////////////////
	VEILCORE_API void TSTMToZuluString(const TsDateStruct_t &tm, tsCryptoStringBase &date);
	////////////////////////////////////////////////////////////////////////////////////////////////////
	/// <summary>Converts an ODBC formatted date into a ZULU date (yyyymmddhhmmssZ)</summary>
	///
	/// <param name="odbc">The ODBC date.</param>
	/// <param name="zulu">[out] The zulu date.</param>
	///
	/// <returns>true if it succeeds, false if it fails.</returns>
	////////////////////////////////////////////////////////////////////////////////////////////////////
	VEILCORE_API bool ODBCDateToZulu(const tsCryptoStringBase &odbc, tsCryptoStringBase &zulu);
	////////////////////////////////////////////////////////////////////////////////////////////////////
	/// <summary>Converts a ZULU formatted date into an ODBC date.</summary>
	///
	/// <param name="zulu">The zulu date.</param>
	/// <param name="odbc">[out] The ODBC date.</param>
	///
	/// <returns>true if it succeeds, false if it fails.</returns>
	////////////////////////////////////////////////////////////////////////////////////////////////////
	VEILCORE_API bool ZuluToODBCDate(const tsCryptoStringBase &zulu, tsCryptoStringBase &odbc);
	////////////////////////////////////////////////////////////////////////////////////////////////////
	/// <summary>Queries a ZULU time to see if it is valid</summary>
	///
	/// <param name="zulu">The zulu time.</param>
	///
	/// <returns>true if it succeeds, false if it fails.</returns>
	////////////////////////////////////////////////////////////////////////////////////////////////////
	VEILCORE_API bool ZuluTimeIsValid(const tsCryptoStringBase &zulu);
	////////////////////////////////////////////////////////////////////////////////////////////////////
	/// @fn	bool isZulu(tsCryptoString str)
	///
	/// @brief	Query if 'str' is zulu.
	///
	/// @author	Rogerb
	/// @date	10/31/2010
	///
	/// @param	str	The string.
	///
	/// @return	true if zulu, false if not.
	////////////////////////////////////////////////////////////////////////////////////////////////////
	bool VEILCORE_API isZulu(const tsCryptoStringBase &str);
	////////////////////////////////////////////////////////////////////////////////////////////////////
	/// @fn	bool isDateTime(tsCryptoString str)
	///
	/// @brief	Query if 'str' is date time.
	///
	/// @author	Rogerb
	/// @date	10/31/2010
	///
	/// @param	str	The string.
	///
	/// @return	true if date time, false if not.
	////////////////////////////////////////////////////////////////////////////////////////////////////
	bool VEILCORE_API isDateTime(const tsCryptoStringBase &str);
	////////////////////////////////////////////////////////////////////////////////////////////////////
	/// @fn	tsCryptoString DateTimeToZulu(tsCryptoStringBase dateTime)
	///
	/// @brief	Date time to zulu.
	///
	/// @author	Rogerb
	/// @date	10/31/2010
	///
	/// @param	dateTime	Time of the date.
	///
	/// @return	.
	////////////////////////////////////////////////////////////////////////////////////////////////////
	tsCryptoString VEILCORE_API DateTimeToZulu(const tsCryptoStringBase &_dateTime);
	////////////////////////////////////////////////////////////////////////////////////////////////////
	/// @fn	tsCryptoString ZuluToDateTime(tsCryptoString zuluTime)
	///
	/// @brief	Zulu to date time.
	///
	/// @author	Rogerb
	/// @date	10/31/2010
	///
	/// @param	zuluTime	Time of the zulu.
	///
	/// @return	.
	////////////////////////////////////////////////////////////////////////////////////////////////////
	tsCryptoString VEILCORE_API ZuluToDateTime(const tsCryptoStringBase &_zuluTime);
	VEILCORE_API int64_t GetTicks();

//#ifdef _WIN32
//	////////////////////////////////////////////////////////////////////////////////////////////////////
//	/// <summary>VARIANT to OLE date.</summary>
//	///
//	/// <param name="from">VARIANT holding the date information.</param>
//	/// <param name="to">  [out] The OLE date.</param>
//	///
//	/// <returns>S_OK for success or a standard COM error code for failure.</returns>
//	////////////////////////////////////////////////////////////////////////////////////////////////////
//	bool VEILCORE_API TSCKMDATEToDATE(VARIANT from, double *to);
//	////////////////////////////////////////////////////////////////////////////////////////////////////
//	/// <summary>Converts an OLE date to a VARIANT</summary>
//	///
//	/// <param name="from">The OLE date</param>
//	/// <param name="to">  [out] The VARIANT.</param>
//	///
//	/// <returns>S_OK for success or a standard COM error code for failure</returns>
//	////////////////////////////////////////////////////////////////////////////////////////////////////
//	bool VEILCORE_API TSDATEToCKMDATE(double from, VARIANT *to);
//#endif // _WIN32
	////////////////////////////////////////////////////////////////////////////////////////////////////
	/// <summary>Converts a date into a Julian value</summary>
	///
	/// <param name="wYear"> The year.</param>
	/// <param name="wMonth">The month.</param>
	/// <param name="wDay">  The day.</param>
	///
	/// \warning This function assumes that the calendar of Jan 1, 0001 was exactly the same as it is now.
	///          This is not the case but most people do not need that level of accuracy for such old dates.
	///
	/// <returns>The number of days since Jan 1, 0001 where Jan 1, 0001 is a value of 1.</returns>
	////////////////////////////////////////////////////////////////////////////////////////////////////
	int32_t VEILCORE_API TsDateStruct_ttoJulian(uint16_t wYear, uint16_t wMonth, uint16_t wDay);
	////////////////////////////////////////////////////////////////////////////////////////////////////
	/// <summary>Converts a date and time into a Julian value.</summary>
	///
	/// <param name="wYear">	   The year.</param>
	/// <param name="wMonth">	   The month.</param>
	/// <param name="wDay">		   The day.</param>
	/// <param name="mHour">	   The hour.</param>
	/// <param name="mMinute">	   The minute.</param>
	/// <param name="mSecond">	   The second.</param>
	/// <param name="mMillisecond">The millisecond.</param>
	///
	/// \warning This function assumes that the calendar of Jan 1, 0001 was exactly the same as it is now.
	///          This is not the case but most people do not need that level of accuracy for such old dates.
	///
	/// <returns>The number of days since Jan 1, 0001 where Jan 1, 0001 is a value of 1.</returns>
	////////////////////////////////////////////////////////////////////////////////////////////////////
	double VEILCORE_API TsDateStruct_ttoJulian(uint16_t wYear, uint16_t wMonth, uint16_t wDay, uint16_t mHour, uint16_t mMinute, uint16_t mSecond, uint16_t mMillisecond);
	////////////////////////////////////////////////////////////////////////////////////////////////////
	/// <summary>Converts a Julian date into the TsDateStruct_t structure</summary>
	///
	/// <param name="dtSrc"> The source date and type.</param>
	/// <param name="tmDest">[out] The converted date.</param>
	///
	/// <returns>true if it succeeds, false if it fails.</returns>
	////////////////////////////////////////////////////////////////////////////////////////////////////
	bool VEILCORE_API JulianToTsDateStruct_t(double dtSrc, TsDateStruct_t *tmDest);

	////////////////////////////////////////////////////////////////////////////////////////////////////
	/// <summary>A macro that defines OLE datetime error.</summary>
	////////////////////////////////////////////////////////////////////////////////////////////////////
#define AFX_OLE_DATETIME_ERROR (-1)
////////////////////////////////////////////////////////////////////////////////////////////////////
/// <summary>A macro that defines one half second as an OLE datetime.</summary>
////////////////////////////////////////////////////////////////////////////////////////////////////
#define AFX_OLE_DATETIME_HALFSECOND (1.0 / (2.0 * (60.0 * 60.0 * 24.0)))


/// <summary>Date conversion and manipulation class</summary>
	class VEILCORE_API tsCryptoDate
	{
		// Constructors
	public:

		static void* operator new(std::size_t count) {
			return tscrypto::cryptoNew(count);
		}
		static void* operator new[](std::size_t count) {
			return tscrypto::cryptoNew(count);
		}
			static void operator delete(void* ptr) {
			tscrypto::cryptoDelete(ptr);
		}
		static void operator delete[](void* ptr) {
			tscrypto::cryptoDelete(ptr);
		}

		/// <summary>Type of the date conversion</summary>
		typedef enum {
			Zulu,		///< Zulu date and time  YYYYMMDDhhmmssZ
			ZuluUTC, 	///< Zulu date and time  YYMMDDhhmmssZ
			ISO8601,		///< ISO 8601 formatted date and time   yyyy-mm-ddThh:mm:ss:mmm
			ODBC            ///< ODBC formatted date and time
		} ConversionType;

		////////////////////////////////////////////////////////////////////////////////////////////////////
		/// <summary>Gets current date and time.</summary>
		///
		/// <returns>The current date and time.</returns>
		////////////////////////////////////////////////////////////////////////////////////////////////////
		static tsCryptoDate GetCurrentTime();
		////////////////////////////////////////////////////////////////////////////////////////////////////
		/// <summary>Gets current date and time.</summary>
		///
		/// <returns>The current date and time.</returns>
		////////////////////////////////////////////////////////////////////////////////////////////////////
		static tsCryptoDate Now() { return GetCurrentTime(); }
		////////////////////////////////////////////////////////////////////////////////////////////////////
		/// <summary>Converts the ZULU date into a tsCryptoDate</summary>
		///
		/// <param name="zulu">The zulu date.</param>
		///
		/// <returns>The tsData.</returns>
		////////////////////////////////////////////////////////////////////////////////////////////////////
		static tsCryptoDate DateFromZulu(const tsCryptoStringBase &zulu);
		////////////////////////////////////////////////////////////////////////////////////////////////////
		/// <summary>Converts the ZULU UTC date into a tsCryptoDate</summary>
		///
		/// <param name="zulu">The zulu UTC date.</param>
		///
		/// <returns>The tsData.</returns>
		////////////////////////////////////////////////////////////////////////////////////////////////////
		static tsCryptoDate DateFromZuluUTC(const tsCryptoStringBase &zulu);
		////////////////////////////////////////////////////////////////////////////////////////////////////
		/// <summary>Converts the ISO 8601 date into a tsCryptoDate</summary>
		///
		/// <param name="zulu">The ISO 8601 date.</param>
		///
		/// <returns>The tsData.</returns>
		////////////////////////////////////////////////////////////////////////////////////////////////////
		static tsCryptoDate DateFromISO8601(const tsCryptoStringBase &iso);
		/**
		 * \brief Date from ODBC date string.
		 *
		 * \param odbc The ODBC date.
		 *
		 * \return A tsCryptoDate.
		 */
		static tsCryptoDate DateFromODBC(const tsCryptoStringBase& odbc);

		/// <summary>Default constructor.</summary>
		tsCryptoDate();

		////////////////////////////////////////////////////////////////////////////////////////////////////
		/// <summary>Copy constructor.</summary>
		///
		/// <param name="dateSrc">The date source.</param>
		////////////////////////////////////////////////////////////////////////////////////////////////////
		tsCryptoDate(const tsCryptoDate& dateSrc);
		////////////////////////////////////////////////////////////////////////////////////////////////////
		/// <summary>Creates a tsCryptoDate from a TsDateStruct_t</summary>
		///
		/// <param name="systimeSrc">The TsDateStruct_t date and time.</param>
		////////////////////////////////////////////////////////////////////////////////////////////////////
		tsCryptoDate(const TsDateStruct_t& systimeSrc);
		////////////////////////////////////////////////////////////////////////////////////////////////////
		/// <summary>Constructor.</summary>
		///
		/// <param name="filetimeSrc">The filetime source.</param>
		////////////////////////////////////////////////////////////////////////////////////////////////////
		tsCryptoDate(uint64_t filetimeSrc);
		////////////////////////////////////////////////////////////////////////////////////////////////////
		/// <summary>Constructor.</summary>
		///
		/// <param name="nYear"> The year.</param>
		/// <param name="nMonth">The month.</param>
		/// <param name="nDay">  The day.</param>
		/// <param name="nHour"> The hour.</param>
		/// <param name="nMin">  The minimum.</param>
		/// <param name="nSec">  The second.</param>
		////////////////////////////////////////////////////////////////////////////////////////////////////
		tsCryptoDate(int nYear, int nMonth, int nDay, int nHour, int nMin, int nSec);
//#ifdef _WIN32
//		////////////////////////////////////////////////////////////////////////////////////////////////////
//		/// <summary>Constructor.</summary>
//		///
//		/// <param name="oleDate">OLE date</param>
//		////////////////////////////////////////////////////////////////////////////////////////////////////
//		tsCryptoDate(DATE oleDate);
//#endif // _WIN32

		////////////////////////////////////////////////////////////////////////////////////////////////////
		/// <summary>Constructor.</summary>
		///
		/// <param name="src"> Source date in Ascii form.</param>
		/// <param name="type">The formatting style of the date.</param>
		////////////////////////////////////////////////////////////////////////////////////////////////////
		tsCryptoDate(const tsCryptoStringBase &src, ConversionType type);
		/// <summary>Destructor.</summary>
		~tsCryptoDate();

		//#ifdef _WIN32
		//    ////////////////////////////////////////////////////////////////////////////////////////////////////
		//    /// <summary>Object allocation operator.</summary>
		//    ///
		//    /// <param name="bytes">The number of bytes to allocate.</param>
		//    ///
		//    /// <returns>The allocated object.</returns>
		//    ////////////////////////////////////////////////////////////////////////////////////////////////////
		//    void *operator new(size_t bytes);
		//    ////////////////////////////////////////////////////////////////////////////////////////////////////
		//    /// <summary>Object de-allocation operator.</summary>
		//    ///
		//    /// <param name="ptr">[in,out] If non-null, the pointer to delete.</param>
		//    ////////////////////////////////////////////////////////////////////////////////////////////////////
		//    void operator delete(void *ptr);
		//#endif // _WIN32

		// Attributes
	public:

		/// <summary>Values that represent DateTimeStatus.</summary>
		enum DateTimeStatus
		{
			valid = 0,  ///< The date is valid
			invalid = 1,	///< The date is invalid
			null = 2,   ///< The date is empty
		};

		/// <summary>Clears this object to its blank/initial state.</summary>
		void clear();
		////////////////////////////////////////////////////////////////////////////////////////////////////
		/// <summary>Sets the status.</summary>
		///
		/// <param name="status">The status.</param>
		///
		/// <returns>A reference to this object.</returns>
		////////////////////////////////////////////////////////////////////////////////////////////////////
		tsCryptoDate &SetStatus(DateTimeStatus status);
		////////////////////////////////////////////////////////////////////////////////////////////////////
		/// <summary>Gets the status.</summary>
		///
		/// <returns>The status.</returns>
		////////////////////////////////////////////////////////////////////////////////////////////////////
		DateTimeStatus GetStatus() const;

		////////////////////////////////////////////////////////////////////////////////////////////////////
		/// <summary>Gets as a TsDateStruct_t.</summary>
		///
		/// <param name="sysTime">[out] Date and time in a TsDateStruct_t structure.</param>
		///
		/// <returns>true if it succeeds, false if it fails.</returns>
		////////////////////////////////////////////////////////////////////////////////////////////////////
		bool GetAsSystemTime(TsDateStruct_t& sysTime) const;
		////////////////////////////////////////////////////////////////////////////////////////////////////
		/// <summary>Gets as zulu time.</summary>
		///
		/// <param name="zTime">[out] The date and time.</param>
		///
		/// <returns>true if it succeeds, false if it fails.</returns>
		////////////////////////////////////////////////////////////////////////////////////////////////////
		bool GetAsZuluTime(tsCryptoStringBase &zTime) const;
		/**
		 * \brief Gets as ODBC time.
		 *
		 * \param [in,out] sOdbc The ODBC time string.
		 *
		 * \return true if it succeeds, false if it fails.
		 */
		bool GetAsODBCTime(tsCryptoStringBase& sOdbc) const;
		////////////////////////////////////////////////////////////////////////////////////////////////////
		/// <summary>Gets as zulu UTC time.</summary>
		///
		/// <param name="zTime">[out] The date and time.</param>
		///
		/// <returns>true if it succeeds, false if it fails.</returns>
		////////////////////////////////////////////////////////////////////////////////////////////////////
		bool GetAsZuluUTCTime(tsCryptoStringBase &zTime) const;
		////////////////////////////////////////////////////////////////////////////////////////////////////
		/// <summary>Get the date and time as an ISO 8601 formatted string.</summary>
		///
		/// <param name="isoTime">[out] The string in ISO 8601 format.</param>
		///
		/// <returns>true if it succeeds, false if it fails.</returns>
		////////////////////////////////////////////////////////////////////////////////////////////////////
		bool GetAsISO8601Time(tsCryptoStringBase &isoTime) const;

		////////////////////////////////////////////////////////////////////////////////////////////////////
		/// <summary>Converts this object to a system time.</summary>
		///
		/// <returns>TsDateStruct_t.</returns>
		////////////////////////////////////////////////////////////////////////////////////////////////////
		TsDateStruct_t AsSystemTime() const;
		////////////////////////////////////////////////////////////////////////////////////////////////////
		/// <summary>Converts this object to a zulu time.</summary>
		///
		/// <returns>String as a Zulu time.</returns>
		////////////////////////////////////////////////////////////////////////////////////////////////////
		tsCryptoString AsZuluTime() const;
		/**
		 * \brief Converts this object to an ODBC time string.
		 *
		 * \return A tsCryptoString.
		 */
		tsCryptoString AsODBCTime() const;
		////////////////////////////////////////////////////////////////////////////////////////////////////
		/// <summary>Converts this object to a zulu UTC time.</summary>
		///
		/// <returns>String as a Zulu UTC time.</returns>
		////////////////////////////////////////////////////////////////////////////////////////////////////
		tsCryptoString AsZuluUTCTime() const;
		////////////////////////////////////////////////////////////////////////////////////////////////////
		/// <summary>Converts this object to an ISO 8601 time.</summary>
		///
		/// <returns>String as an ISO 8601 string.</returns>
		////////////////////////////////////////////////////////////////////////////////////////////////////
		tsCryptoString AsISO8601Time() const;

		////////////////////////////////////////////////////////////////////////////////////////////////////
		/// <summary>Gets the year.</summary>
		///
		/// <returns>The year.</returns>
		////////////////////////////////////////////////////////////////////////////////////////////////////
		int GetYear() const;
		////////////////////////////////////////////////////////////////////////////////////////////////////
		/// <summary>Gets the month.</summary>
		///
		/// <returns>The month (1 = Jan).</returns>
		////////////////////////////////////////////////////////////////////////////////////////////////////
		int GetMonth() const;
		////////////////////////////////////////////////////////////////////////////////////////////////////
		/// <summary>Gets the day.</summary>
		///
		/// <returns>The day (1-31).</returns>
		////////////////////////////////////////////////////////////////////////////////////////////////////
		int GetDay() const;
		////////////////////////////////////////////////////////////////////////////////////////////////////
		/// <summary>Gets the hour.</summary>
		///
		/// <returns>The hour (0-23).</returns>
		////////////////////////////////////////////////////////////////////////////////////////////////////
		int GetHour() const;
		////////////////////////////////////////////////////////////////////////////////////////////////////
		/// <summary>Gets the minute.</summary>
		///
		/// <returns>The minute (0-59).</returns>
		////////////////////////////////////////////////////////////////////////////////////////////////////
		int GetMinute() const;
		////////////////////////////////////////////////////////////////////////////////////////////////////
		/// <summary>Gets the second.</summary>
		///
		/// <returns>The second (0-59).</returns>
		////////////////////////////////////////////////////////////////////////////////////////////////////
		int GetSecond() const;

		int GetDayOfWeek() const;

		// Operations
	public:
		////////////////////////////////////////////////////////////////////////////////////////////////////
		/// <summary>Assignment operator.</summary>
		///
		/// <param name="dateSrc">The date source.</param>
		///
		/// <returns>A reference to this object.</returns>
		////////////////////////////////////////////////////////////////////////////////////////////////////
		const tsCryptoDate& operator=(const tsCryptoDate& dateSrc);

		////////////////////////////////////////////////////////////////////////////////////////////////////
		/// <summary>Assignment operator.</summary>
		///
		/// <param name="systimeSrc">The systime source.</param>
		///
		/// <returns>A reference to this object.</returns>
		////////////////////////////////////////////////////////////////////////////////////////////////////
		const tsCryptoDate& operator=(const TsDateStruct_t& systimeSrc);
		////////////////////////////////////////////////////////////////////////////////////////////////////
		/// <summary>Assignment operator.</summary>
		///
		/// <param name="filetimeSrc">The filetime source.</param>
		///
		/// <returns>A reference to this object.</returns>
		////////////////////////////////////////////////////////////////////////////////////////////////////
		const tsCryptoDate& operator=(uint64_t filetimeSrc);

		////////////////////////////////////////////////////////////////////////////////////////////////////
		/// <summary>Equality operator.</summary>
		///
		/// <param name="date">The date to compare.</param>
		///
		/// <returns>true if this object is equal to the parameter.</returns>
		////////////////////////////////////////////////////////////////////////////////////////////////////
		bool operator==(const tsCryptoDate& date) const;
		////////////////////////////////////////////////////////////////////////////////////////////////////
		/// <summary>Inequality operator.</summary>
		///
		/// <param name="date">The date to compare.</param>
		///
		/// <returns>true if this object is not equal to the parameter.</returns>
		////////////////////////////////////////////////////////////////////////////////////////////////////
		bool operator!=(const tsCryptoDate& date) const;
		////////////////////////////////////////////////////////////////////////////////////////////////////
		/// <summary>Less than operator.</summary>
		///
		/// <param name="date">The date to compare.</param>
		///
		/// <returns>true if this object is less than the parameter.</returns>
		////////////////////////////////////////////////////////////////////////////////////////////////////
		bool operator<(const tsCryptoDate& date) const;
		////////////////////////////////////////////////////////////////////////////////////////////////////
		/// <summary>Greater than operator.</summary>
		///
		/// <param name="date">The date to compare.</param>
		///
		/// <returns>true if this object is greater than the parameter.</returns>
		////////////////////////////////////////////////////////////////////////////////////////////////////
		bool operator>(const tsCryptoDate& date) const;
		////////////////////////////////////////////////////////////////////////////////////////////////////
		/// <summary>Less than or equal to operator.</summary>
		///
		/// <param name="date">The date to compare.</param>
		///
		/// <returns>true if this object is less than or equal to the parameter.</returns>
		////////////////////////////////////////////////////////////////////////////////////////////////////
		bool operator<=(const tsCryptoDate& date) const;
		////////////////////////////////////////////////////////////////////////////////////////////////////
		/// <summary>Greater than or equal to operator.</summary>
		///
		/// <param name="date">The date to compare.</param>
		///
		/// <returns>true if this object is greater than or equal to the parameter.</returns>
		////////////////////////////////////////////////////////////////////////////////////////////////////
		bool operator>=(const tsCryptoDate& date) const;

		////////////////////////////////////////////////////////////////////////////////////////////////////
		/// <summary>Sets date time.</summary>
		///
		/// <param name="nYear"> The year.</param>
		/// <param name="nMonth">The month.</param>
		/// <param name="nDay">  The day.</param>
		/// <param name="nHour"> The hour.</param>
		/// <param name="nMin">  The minute.</param>
		/// <param name="nSec">  The second.</param>
		///
		/// <returns>A reference to this object.</returns>
		////////////////////////////////////////////////////////////////////////////////////////////////////
		tsCryptoDate &SetDateTime(int nYear, int nMonth, int nDay, int nHour, int nMin, int nSec);
		////////////////////////////////////////////////////////////////////////////////////////////////////
		/// <summary>Sets date time from zulu.</summary>
		///
		/// <param name="sZuluTime">Date and time in ZULU.</param>
		///
		/// <returns>A reference to this object.</returns>
		////////////////////////////////////////////////////////////////////////////////////////////////////
		tsCryptoDate &SetDateTimeFromZulu(const tsCryptoStringBase &sZuluTime);
		/**
		 * \brief Sets date time from an ODBC string.
		 *
		 * \param sOdbc The ODBC string.
		 *
		 * \return A tsCryptoDate&amp;
		 */
		tsCryptoDate &SetDateTimeFromODBC(const tsCryptoStringBase &sOdbc);
		////////////////////////////////////////////////////////////////////////////////////////////////////
		/// <summary>Sets date time from zulu UTC.</summary>
		///
		/// <param name="sZuluTime">Date and time in ZULU UTC.</param>
		///
		/// <returns>A reference to this object.</returns>
		////////////////////////////////////////////////////////////////////////////////////////////////////
		tsCryptoDate &SetDateTimeFromZuluUTC(const tsCryptoStringBase &sZuluTime);
		////////////////////////////////////////////////////////////////////////////////////////////////////
		/// <summary>Sets date time from ISO 8601.</summary>
		///
		/// <param name="s8601">Date and time in ISO 8601 format.</param>
		///
		/// <returns>A reference to this object.</returns>
		////////////////////////////////////////////////////////////////////////////////////////////////////
		tsCryptoDate &SetDateTimeFromISO8601(const tsCryptoStringBase &s8601); // ODBC Canonical (SQL Server style 120) yyyy-mm-dd hh:mm:ss
		////////////////////////////////////////////////////////////////////////////////////////////////////
		/// <summary>Sets date time from now.</summary>
		///
		/// <returns>A reference to this object.</returns>
		////////////////////////////////////////////////////////////////////////////////////////////////////
		tsCryptoDate &SetDateTimeFromNow();
		////////////////////////////////////////////////////////////////////////////////////////////////////
		/// <summary>Sets a date.</summary>
		///
		/// <param name="nYear"> The year.</param>
		/// <param name="nMonth">The month.</param>
		/// <param name="nDay">  The day.</param>
		///
		/// <returns>A reference to this object.</returns>
		////////////////////////////////////////////////////////////////////////////////////////////////////
		tsCryptoDate &SetDate(uint32_t nYear, uint32_t nMonth, uint32_t nDay);
		////////////////////////////////////////////////////////////////////////////////////////////////////
		/// <summary>Sets a time.</summary>
		///
		/// <param name="nHour">The hour.</param>
		/// <param name="nMin"> The minute.</param>
		/// <param name="nSec"> The second.</param>
		///
		/// <returns>A reference to this object.</returns>
		////////////////////////////////////////////////////////////////////////////////////////////////////
		tsCryptoDate &SetTime(uint32_t nHour, uint32_t nMin, uint32_t nSec);
		////////////////////////////////////////////////////////////////////////////////////////////////////
		/// <summary>Adds an interval.</summary>
		///
		/// <param name="lDays"> The days.</param>
		/// <param name="nHours">The hours.</param>
		/// <param name="nMins"> The mins.</param>
		/// <param name="nSecs"> The seconds.</param>
		///
		/// <returns>A reference to this object.</returns>
		////////////////////////////////////////////////////////////////////////////////////////////////////
		tsCryptoDate &AddInterval(int32_t lDays, int32_t nHours, int32_t nMins, int32_t nSecs);

//#ifdef _WIN32
//		////////////////////////////////////////////////////////////////////////////////////////////////////
//		/// <summary>Converts this object to an OLE date.</summary>
//		///
//		/// <returns>This object as a DATE.</returns>
//		////////////////////////////////////////////////////////////////////////////////////////////////////
//		DATE ToOleDate();
//#endif // _WIN32

		////////////////////////////////////////////////////////////////////////////////////////////////////
		/// <summary>Converts this object to a zulu time.</summary>
		///
		/// <returns>This object as a tsCryptoString.</returns>
		////////////////////////////////////////////////////////////////////////////////////////////////////
		tsCryptoString ToZuluTime() const;
		/**
		 * \brief Converts this object to an ODBC string.
		 *
		 * \return This object as an ODBC string.
		 */
		tsCryptoString ToODBC() const;
		////////////////////////////////////////////////////////////////////////////////////////////////////
		/// <summary>Converts this object to a zulu UTC time.</summary>
		///
		/// <returns>This object as a tsCryptoString.</returns>
		////////////////////////////////////////////////////////////////////////////////////////////////////
		tsCryptoString ToZuluUTCTime() const;
		////////////////////////////////////////////////////////////////////////////////////////////////////
		/// <summary>Converts this object to an ISO 8601 time.</summary>
		///
		/// <returns>This object as a tsCryptoString.</returns>
		////////////////////////////////////////////////////////////////////////////////////////////////////
		tsCryptoString ToISO8601Time() const;

//#ifdef _WIN32
//		////////////////////////////////////////////////////////////////////////////////////////////////////
//		/// <summary>Initializes this object from the given OLE date.</summary>
//		///
//		/// <param name="oleDate">OLE date.</param>
//		///
//		/// <returns>true if it succeeds, false if it fails.</returns>
//		////////////////////////////////////////////////////////////////////////////////////////////////////
//		bool FromOleDate(DATE oleDate);
//#endif // _WIN32

		tsCryptoString ToString() const;
		tsCryptoString ToDateString() const;
		tsCryptoString ToTimeString() const;
		tsCryptoDate ToUTC() const;
		tsCryptoDate ToLocal() const;
	protected:
		/// <summary>Check range.</summary>
		void CheckRange();
		////////////////////////////////////////////////////////////////////////////////////////////////////
		/// <summary>Validates that the specified portion of the string is all numbers</summary>
		///
		/// <param name="str">The string to check.</param>
		/// <param name="len">The length of the string to check.</param>
		///
		/// <returns>true if it succeeds, false if it fails.</returns>
		////////////////////////////////////////////////////////////////////////////////////////////////////
		bool AllNumbers(const char *str, int len);

	protected:
		TsDateStruct_t m_dt;
		DateTimeStatus m_status;
	};
}

#endif // __TSCRYPTODATE_H__

