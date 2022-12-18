#pragma once
#include <iostream>
#include <iomanip>
#include <vector>
#include <string>
#include <sstream>
#include <cmath>
using std::ostream;
using std::string;
using std::vector;


class TablePrinter 
{
    //template<typename T> 
    //void OutputDecimalNumber(T input);
    void PrintHorizontalLine();

    static string _nonSeparator;
    ostream* _outStream;
    vector<string> _columnHeaders;
    vector<int> _columnWidths;
    string _separator;

    int _currentRow;
    int _currentColumn;

    int _tableWidth;
    bool _flushLeft;
public:
    TablePrinter(ostream* output, const string& separator = "|");
    ~TablePrinter();

    int GetNumColumns();
    int GetTableWidth();
    void SetSeparator(const string& separator);
    void SetFlushLeft();
    void SetFlushRight();

    void AddColumn(const string& header_name, int column_width);
    void PrintHeader();
    void PrintFooter();

    template<typename T> 
    TablePrinter& operator<<(T input) 
    {
        if (_currentColumn == 0)
            *_outStream << "|";

        if (_flushLeft)
            *_outStream << std::left;
        else
            *_outStream << std::right;

        // ��������� 3 ������ ����� ��� ��������������, ����, ��������������
        *_outStream << std::setw(_columnWidths.at(_currentColumn))
            << input;

        if (_currentColumn == GetNumColumns() - 1) {
            *_outStream << "|\n";
            _currentRow = _currentRow + 1;
            _currentColumn = 0;
        }
        else {
            *_outStream << _separator;
            _currentColumn = _currentColumn + 1;
        }

        return *this;
    }
};