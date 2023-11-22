#include "defines.h"
#include "TUI.h"
#include <sstream>
#include "agentcluster.h"
#include "stopwatch.h"

class GUI
{
  unsigned x_dim;
  unsigned y_dim;
  void appendString(char *p, int *pos, char *other, int size)
  {
    for (unsigned i = 0; i < size; i++)
    {
      p[*pos + i] = other[i];
    }
    *pos += size;
  }
  void moveCursorIntrisicly(char *p, int *pos, int x, int y)
  {
    int size = snprintf(NULL, 0, "\x1b[%d;%df", x, y);
    char *a = new char[size + 1];
    sprintf(a, "\x1b[%d;%df", x, y);
    appendString(p, pos, a, size);
    delete[] a;
  }

public:
  void hideCursor()
  {
    printf("\x1b[?25l");
  }
  GUI(unsigned x, unsigned y) : x_dim(x), y_dim(y)
  {
  }
  GUI()
  {
    x_dim = BORDER_X_MAX;
    y_dim = BORDER_Y_MAX;
  }

  void emptyCanvasSlow()
  {
    for (unsigned i = 0; i < x_dim; i++)
    {
      moveTo(i, 0);
      for (unsigned j = 0; j < y_dim; j++)
      {
        printf("%c", ' ');
        moveTo(i, j);
      }
    }
  }
  void emptyCanvas()
  {
    hideCursor();
    std::ostringstream result;
    for (unsigned i = 0; i < x_dim; i++)
    {
      result << "\x1b[" << i << ";" << 0 << "f";
      for (unsigned j = 0; j < y_dim; j++)
      {
        result << ' ';
        result << "\x1b[" << i << ";" << j << "f";
      }
    }
    printf(result.str().c_str());
  }

  void emptyCanvasEvenFaster()
  {
    char *res = new char[100 * x_dim * y_dim];
    int pos = 0;
    for (unsigned i = 0; i < x_dim; i++)
    {
      moveCursorIntrisicly(res, &pos, i, 0);

      for (unsigned j = 0; j < y_dim; j++)
      {
        appendString(res, &pos, " ", 1);
        moveCursorIntrisicly(res, &pos, i, j);
      }
    }
    pos += 1;
    res[pos] = '\0';

    printf(res);
    //fflush(stdout);
    //write(1, res, pos);
    delete[] res;
  }

  void clearAll()
  {
    hideCursor();
    std::ostringstream result;
    for (unsigned i = 0; i < 200; i++)
    {
      result << "\x1b[" << i << ";" << 0 << "f";
      for (unsigned j = 0; j < 200; j++)
      {
        result << ' ';
        result << "\x1b[" << i << ";" << j << "f";
      }
    }
    printf(result.str().c_str());
  }
  void printField(Vector<Vector<AgentCluster>>& v, Stopwatch & sw)
  {
    float average_all = 0, count = 0; 
    unsigned peakGrade = 0; 
    std::ostringstream result;
    //result << "\x1b[38;2;120;0;90m";
    for (unsigned i = 0; i < x_dim; i++)
    {
      result << "\x1b[" << i << ";" << 0 << "f";
      for (unsigned j = 0; j < y_dim; j++)
      {

        const float average = v[i][j].getGradeMedian();
        if ( !v[i][j].empty() )
        {
          average_all += average; 
          ++count; 
          if ( v[i][j].peak() > peakGrade)
            peakGrade = v[i][j].peak(); 
        }
        //result << "\x1b[38;2;20;" << v[i][j].amountOfAgents() * 80 << ";90m";
        //result << "\x1b[38;2;20;" << ((unsigned)average / 50 ) + 20 << ";90m";
        result << "\x1b[38;2;" << v[i][j].getQuantity() *30 << ";" << ((unsigned)average / 50 ) + 20 << ";30m";
                //result << "\x1b[38;2;" <<  v[i][j].amountOfAgents() * 80  << ";" << (unsigned) v[i][j].getGradeMedian() * 80 << ";90m";
        //result << (unsigned )v[i][j].amountOfAgents();
        //result << '_';
        result << "#";
        result << "\x1b[" << i << ";" << j << "f";
      }
    }
    //ignoring 0 division error.
    result << "\x1b[" << x_dim << ";" << 0 << "f"<<  "\x1b[38;2;255;255;255m" << "Average Grade is: " << (average_all / (count)) << "               ";
    sw.finish(); 
    result << "\x1b[" << x_dim + 1 << ";" << 0 << "f"<<  "\x1b[38;2;255;255;255m" << "Time taken (approx): " << sw.getMilliseconds()  << "ms. ";
    result << "\x1b[" << x_dim + 2 << ";" << 0 << "f"<<  "\x1b[38;2;255;255;255m" << "Peak Grade: " << peakGrade << ".";

    printf(result.str().c_str());
    resetColor(); 
    hideCursor(); 
  }
  void LprintField(Vector<Vector<AgentCluster>> v)
  {
    std::wstringstream result;
    //result << "\x1b[38;2;120;0;90m";
    for (unsigned i = 0; i < x_dim; i++)
    {
      result << "\x1b[" << i << ";" << 0 << "f";
      for (unsigned j = 0; j < y_dim; j++)
      {
        result << "\x1b[38;2;20;" << v[i][j].amountOfAgents() * 80 << ";90m";
        //result << "\x1b[38;2;20;" << (unsigned) v[i][j].getGradeMedian() * 80 << ";90m";
        //result << "\x1b[38;2;" <<  v[i][j].amountOfAgents() * 80  << ";" << (unsigned) v[i][j].getGradeMedian() * 80 << ";90m";
        //result << (unsigned )v[i][j].amountOfAgents();
        //result << '_';
        result << L"\u25A0";
        result << "\x1b[" << i << ";" << j << "f";
      }
    }
    wprintf(result.str().c_str());

  }
};
