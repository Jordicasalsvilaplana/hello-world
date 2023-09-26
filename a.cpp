#include <iostream>
#include <string.h>
#include <time.h>
#include <string>

class Tablero
{
public:
   int col, fil;
   int **tableroMinas;
   char **tableroVisto;

   int minasVistas;
   Tablero(int col, int fil, int minasVistas)
   {
      this->col = col;
      this->fil = fil;
      this->minasVistas = minasVistas;
      this->tableroMinas = new int *[fil];
      for (int i = 0; i < fil; i++)
         this->tableroMinas[i] = new int[col];

      this->tableroVisto = new char *[fil];
      for (int i = 0; i < fil; i++)
         this->tableroVisto[i] = new char[col];
   }
};

bool checkMinas(Tablero &t)
{

   for (int i = 0; i < t.fil; i++)
   {
      for (int j = 0; j < t.col; j++)
      {
         if (t.tableroMinas[i][j] >= 9 && t.tableroVisto[i][j] == ' ')
         {
            return false;
         }
      }
   }
   return true;
}

void printTablero(Tablero &t)
{
   const char *a = "___";
   std::cout << "\n    ";
   for (int i = 0; i < t.col; i++)
   {
      std::cout << i << " ";
   }
   std::cout << "\n";
   for (int i = 0; i < t.col; i++)
   {
      std::cout << a;
   }
   std::cout << "\n";
   for (int i = 0; i < t.fil; i++)
   {
      std::cout << i << " | ";
      for (int j = 0; j < t.col; j++)
      {

         if (t.tableroVisto[i][j] == ' ')
         {
            switch (t.tableroMinas[i][j])
            {
            case 0 ... 8:
               std::cout << t.tableroMinas[i][j] << " ";
               break;
            case 9 ... 100:
               std::cout << "* ";
               break;
            default:
               break;
            }
         }
         else if (t.tableroVisto[i][j] == 'X')
         {
            std::cout << "X ";
         }
      }
      std::cout << "\n";
   }

   for (int i = 0; i < t.col; i++)
   {
      std::cout << a;
   }
   std::cout << "\n    ";
   for (int i = 0; i < t.col; i++)
   {
      std::cout << i << " ";
   }

   std::cout << "\n";
}

void initializeTablero(Tablero &t)
{

   for (int i = 0; i < t.fil; i++)
   {
      for (int j = 0; j < t.col; j++)
      {
         t.tableroMinas[i][j] = 0;
         t.tableroVisto[i][j] = 'X';
      }
   }
   for (int i = 0; i < t.minasVistas; i++)
   {
      int fil = rand() % t.fil;
      int col = rand() % t.col;

      if (t.tableroMinas[fil][col] != 9)
      {
         t.tableroMinas[fil][col] = 9;
      }

      if (fil == 0 && col == 0)
      {
         t.tableroMinas[fil][col + 1]++;
         t.tableroMinas[fil + 1][col]++;
         t.tableroMinas[fil + 1][col + 1]++;
      }
      else if (fil == t.fil - 1 && col == t.col - 1)
      {
         t.tableroMinas[fil - 1][col - 1]++;
         t.tableroMinas[fil - 1][col]++;
         t.tableroMinas[fil][col - 1]++;
      }
      else if (fil == 0 && col == t.col - 1)
      {
         t.tableroMinas[fil][col - 1]++;
         t.tableroMinas[fil + 1][col - 1]++;
         t.tableroMinas[fil + 1][col]++;
      }
      else if (fil == t.fil - 1 && col == 0)
      {
         t.tableroMinas[fil - 1][col]++;
         t.tableroMinas[fil - 1][col + 1]++;
         t.tableroMinas[fil][col + 1]++;
      }
      else if (fil > 0)
      {
         if (col > 0)
         {
            if (fil < t.fil - 1)
            {
               if (col < t.col - 1)
               {
                  t.tableroMinas[fil - 1][col - 1]++;
                  t.tableroMinas[fil - 1][col]++;
                  t.tableroMinas[fil - 1][col + 1]++;

                  t.tableroMinas[fil][col - 1]++;
                  t.tableroMinas[fil][col + 1]++;

                  t.tableroMinas[fil + 1][col - 1]++;
                  t.tableroMinas[fil + 1][col]++;
                  t.tableroMinas[fil + 1][col + 1]++;
               }
               else if (col == t.col - 1)
               {
                  t.tableroMinas[fil - 1][col - 1]++;
                  t.tableroMinas[fil - 1][col]++;
                  t.tableroMinas[fil][col - 1]++;
                  t.tableroMinas[fil + 1][col - 1]++;
                  t.tableroMinas[fil + 1][col]++;
               }
            }
            else if (fil == t.fil - 1)
            {
               t.tableroMinas[fil - 1][col - 1]++;
               t.tableroMinas[fil - 1][col]++;
               t.tableroMinas[fil - 1][col + 1]++;
               t.tableroMinas[fil][col - 1]++;
               t.tableroMinas[fil][col + 1]++;
            }
         }
         else if (col == 0)
         {
            t.tableroMinas[fil - 1][col]++;
            t.tableroMinas[fil - 1][col + 1]++;
            t.tableroMinas[fil][col + 1]++;
            t.tableroMinas[fil + 1][col]++;
            t.tableroMinas[fil + 1][col + 1]++;
         }
      }
      else if (fil == 0)
      {
         t.tableroMinas[fil][col - 1]++;
         t.tableroMinas[fil][col + 1]++;
         t.tableroMinas[fil + 1][col - 1]++;
         t.tableroMinas[fil + 1][col]++;
         t.tableroMinas[fil + 1][col + 1]++;
      }
   }
}

void getzero(Tablero t, int fil, int col)
{

   if ((fil >= 0 && fil < t.fil && col >= 0 && col < t.col) && t.tableroMinas[fil][col] == 0)
   {

      t.tableroVisto[fil][col] = ' ';

      if (fil == 0 && col == 0)
      {
         getzero(t, ++fil, ++col);
      }
      else if (fil == t.fil - 1 && col == t.col - 1)
      {
         getzero(t, fil, --col);
      }
      else if (fil == 0 && col == t.col - 1)
      {
         getzero(t, ++fil, --col);
      }
      else if (fil == t.fil - 1 && col == 0)
      {
         getzero(t, --fil, ++col);
      }
      else if (fil > 0)
      {
         if (col > 0)
         {
            if (fil < t.fil - 1)
            {
               if (col < t.col - 1)
               {
                  getzero(t, ++fil, col);
               }
               else if (col == t.col - 1)
               {
                  getzero(t, fil, col);
               }
            }
            else if (fil == t.fil - 1)
            {
               getzero(t, --fil, --col);
            }
         }
         else if (col == 0)
         {
            getzero(t, --fil, col);
         }
      }
      else if (fil == 0)
      {
         getzero(t, fil, ++col);
      }
   }
}

void getInput(Tablero t)
{
   int fil, col;
   do
   {
      fil = 0;
      col = 0;
      std::cout << "Digues una posicio (fil col):";
      std::cin >> fil >> col;
   } while (fil < 0 || fil >= t.fil || col < 0 || col >= t.col || t.tableroVisto[fil][col] == ' ');
   t.tableroVisto[fil][col] = ' ';
   getzero(t, fil, col);
}

int main()
{
   srand(time(NULL));

   Tablero t(5, 5, 1);

   initializeTablero(t);
   printTablero(t);
   do
   {
      getInput(t);
      printTablero(t);
   } while (checkMinas(t));

   std::cout << "\nYOU WIN\n";
}
