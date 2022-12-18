#include "TablePrinter.h"
#include <stdexcept>
#include <iomanip>
#include <stdexcept>

TablePrinter::TablePrinter(ostream* output, const string& separator) 
{
    _outStream = output;
    _currentRow = 0;
    _currentColumn = 0;
    _separator = separator;
    _tableWidth = 0;
    _flushLeft = false;
}

TablePrinter::~TablePrinter() {}

int TablePrinter::GetNumColumns() 
{
    return _columnHeaders.size();
}

int TablePrinter::GetTableWidth() 
{
    return _tableWidth;
}

void TablePrinter::SetSeparator(const string& separator) 
{
    _separator = separator;
}

void TablePrinter::SetFlushLeft() 
{
    _flushLeft = true;
}

void TablePrinter::SetFlushRight() 
{
    _flushLeft = false;
}

void TablePrinter::AddColumn(const std::string& headerName, int columnWidth) 
{
    if (columnWidth < 4) {
        throw std::exception("Column size has to be >= 4");
    }

    _columnHeaders.push_back(headerName);
    _columnWidths.push_back(columnWidth);
    _tableWidth += columnWidth + _separator.size();
}

void TablePrinter::PrintHorizontalLine() 
{
    *_outStream << "+"; 

    for (int i = 0; i < _tableWidth - 1; ++i)
        *_outStream << "-";

    *_outStream << "+"; 
    *_outStream << "\n";
}

void TablePrinter::PrintHeader() 
{
    PrintHorizontalLine();
    *_outStream << "|";

    for (int i = 0; i < GetNumColumns(); ++i) 
    {

        if (_flushLeft)
            *_outStream << std::left;
        else
            *_outStream << std::right;

        *_outStream << std::setw(_columnWidths.at(i)) << _columnHeaders.at(i).substr(0, _columnWidths.at(i));
        if (i != GetNumColumns() - 1) {
            *_outStream << _separator;
        }
    }

    *_outStream << "|\n";
    PrintHorizontalLine();
}

void TablePrinter::PrintFooter() {
    PrintHorizontalLine();
}

//TablePrinter& TablePrinter::operator<<(float input) {
//    OutputDecimalNumber<float>(input);
//    return *this;
//}
//
//TablePrinter& TablePrinter::operator<<(double input) {
//    OutputDecimalNumber<double>(input);
//    return *this;
//}