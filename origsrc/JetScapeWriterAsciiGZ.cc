// -----------------------------------------
// JetScape (modular/task) based framework
// Intial Design: Joern Putschke (2017)
//                (Wayne State University)
// -----------------------------------------
// License and Doxygen-like Documentation to be added ...

// jetscape writer ascii + gzip class implementation

#include "JetScapeWriterAsciiGZ.h"
#include "JetScapeLogger.h"

namespace Jetscape {

JetScapeWriterAsciiGZ::JetScapeWriterAsciiGZ(string m_file_name_out)
{
  SetOutputFileName(m_file_name_out);
}

JetScapeWriterAsciiGZ::~JetScapeWriterAsciiGZ()
{
  if (GetActive())
      Close();
}

void JetScapeWriterAsciiGZ::WriteEvent()
{
  JSDEBUG<< GetCurrentEvent() << " Event ";
  output_file<< GetCurrentEvent() << " Event \n";
}

void JetScapeWriterAsciiGZ::Write(weak_ptr<Parton> p)
{
  output_file<<*p.lock()<<endl;
}

void JetScapeWriterAsciiGZ::Write(weak_ptr<Vertex> v)
{
  output_file<<*v.lock()<<endl;
}

void JetScapeWriterAsciiGZ::Write(weak_ptr<Hadron> h)
{
  output_file<<*h.lock()<<endl;
}

void JetScapeWriterAsciiGZ::Init()
{
   if (GetActive())
     {
       INFO<<"JetScape (gzip) Writer initialized with output file = "<<GetOutputFileName();
       output_file.open(GetOutputFileName().c_str());
     }
}

void JetScapeWriterAsciiGZ::Exec()
{
  if (GetActive())
    WriteEvent();
}

} // end namespace Jetscape