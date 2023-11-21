#include "defines.h"
#include "TUI.h"
#include <sstream>
#include "agentcluster.h"

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
  void printField(Vector<Vector<AgentCluster>> v)
  {
    std::ostringstream result;
    for (unsigned i = 0; i < x_dim; i++)
    {
      result << "\x1b[" << i << ";" << 0 << "f";
      for (unsigned j = 0; j < y_dim; j++)
      {
        result << v[i][j].amountOfAgents();
        result << "\x1b[" << i << ";" << j << "f";
      }
    }
    printf(result.str().c_str());

  }
};
