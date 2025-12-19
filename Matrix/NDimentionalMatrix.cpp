#include <iostream>
#include <random>
using namespace std;

class Matrix
{
private:
    double **container;
    int rows;
    int columns;

    void InitializeMatrix()
    {
        this->container = new double *[rows];
        for(int i=0;i<this->rows;i++){
            this->container[i] = new double[columns];
        }
        
        this->ClearMatrix();
    }

    void ClearMatrix(){
        for(int i=0;i<this->rows;i++){
            for(int j=0;j<this->columns;j++){
                this->container[i][j] = 0.0;
            }
        }
    }

    void DeleteMatrix(){
        for(int i=0;i<this->rows;i++){
            delete[] this->container[i];
        }

        delete[] this->container;
        this->container = NULL;
    }

public:
    Matrix()
    {
        this->rows = 4;
        this->columns = 4;
        this->InitializeMatrix();
    }

    Matrix(int rows, int columns){
        this->rows = rows;
        this->columns = columns;
        this->InitializeMatrix();
    }

    ~Matrix(){
        this->DeleteMatrix();
        this->rows = 0;
        this->columns = 0;
    }

    void setDimention(int rows, int columns){
        this->DeleteMatrix();

        this->rows = rows;
        this->columns = columns;

        this->InitializeMatrix();
    }

    pair<int, int> getDimention(){
        return make_pair(this->rows, this->columns);
    }

    void InitializeWithInput(){
        for(int i=0;i<this->rows;i++){
            for(int j=0;j<this->columns;j++){
                cout<<"Enter Value for Index ["<<(i + 1)<<"]["<<(j + 1)<<"]: ";
                cin>>this->container[i][j];
            }
        }
    }

    void InitializeWithRandom(int range){
        // another way of generating a double number randomly
        uniform_real_distribution<double> unif(-range, range);
        default_random_engine re;

        for(int i=0;i<this->rows;i++){
            for(int j=0;j<this->columns;j++){
                this->container[i][j] = unif(re);
            }
        }
    }

    void setIndex(double value, int row, int column){
        this->container[row][column] = value;
    }

    double getIndex(int row, int column){
        return this->container[row][column];
    }

    void clear(){
        if(this->container != NULL){
            this->ClearMatrix();
        }
    }

    void print(){
        cout<<endl;
        for(int i=0;i<this->rows;i++){
            for(int j=0;j<this->columns;j++){
                cout<<this->container[i][j]<<" ";
            }
            cout<<endl;
        }
        cout<<endl;
    }

    void operator=(Matrix &m){
        this->setDimention(m.rows, m.columns);

        for(int i=0;i<this->rows;i++){
            for(int j=0;j<this->columns;j++){
                this->container[i][j] = m.container[i][j];
            }
        }
    }

    Matrix &operator+(Matrix &m){
        Matrix result(this->rows, this->columns);

        if(this->rows == m.rows && this->columns == m.columns){
            for(int i=0;i<this->rows;i++){
                for(int j=0;j<this->columns;j++){
                    result.container[i][j] = (this->container[i][j] + m.container[i][j]);
                }
            }
        }

        return result;
    }

    Matrix &operator-(Matrix &m){
        Matrix result(this->rows, this->columns);
        
        if(this->rows == m.rows && this->columns == m.columns){
            for(int i=0;i<this->rows;i++){
                for(int j=0;j<this->columns;j++){
                    result.container[i][j] = (this->container[i][j] - m.container[i][j]);
                }
            }
        }

        return result;
    }

    Matrix &operator*(Matrix &m){
        Matrix result(this->rows, this->columns);
        
        if(this->rows == m.rows && this->columns == m.columns){
            for(int i=0;i<this->rows;i++){
                for(int j=0;j<this->columns;j++){
                    result.container[i][j] = (this->container[i][j] * m.container[i][j]);
                }
            }
        }

        return result;
    }

    Matrix &operator/(Matrix &m){
        Matrix result(this->rows, this->columns);
        
        if(this->rows == m.rows && this->columns == m.columns){
            for(int i=0;i<this->rows;i++){
                for(int j=0;j<this->columns;j++){
                    result.container[i][j] = (this->container[i][j] / m.container[i][j]);
                }
            }
        }

        return result;
    }

    // % can only be performed on integer values (remember)
};

class MatrixOperation{
public:
    Matrix &Add(Matrix &m1, Matrix &m2){
        pair<int, int> dim1 = m1.getDimention();
        pair<int, int> dim2 = m2.getDimention();

        Matrix result(dim1.first, dim1.second);
        if(dim1.first == dim2.first && dim1.second == dim2.second){
            for(int i=0;i<dim1.first;i++){
                for(int j=0;j<dim1.second;j++){
                    result.setIndex((m1.getIndex(i, j) + m2.getIndex(i, j)), i, j);
                }
            }
        }

        return result;
    }

    Matrix &Subtract(Matrix &m1, Matrix &m2){
        pair<int, int> dim1 = m1.getDimention();
        pair<int, int> dim2 = m2.getDimention();

        Matrix result(dim1.first, dim1.second);
        if(dim1.first == dim2.first && dim1.second == dim2.second){
            for(int i=0;i<dim1.first;i++){
                for(int j=0;j<dim1.second;j++){
                    result.setIndex((m1.getIndex(i, j) - m2.getIndex(i, j)), i, j);
                }
            }
        }

        return result;
    }

    Matrix &Multiply(Matrix &m1, Matrix &m2){
        pair<int, int> dim1 = m1.getDimention();
        pair<int, int> dim2 = m2.getDimention();

        Matrix result(dim1.first, dim1.second);
        if(dim1.first == dim2.first && dim1.second == dim2.second){
            for(int i=0;i<dim1.first;i++){
                for(int j=0;j<dim1.second;j++){
                    result.setIndex((m1.getIndex(i, j) * m2.getIndex(i, j)), i, j);
                }
            }
        }

        return result;
    }

    Matrix &Divide(Matrix &m1, Matrix &m2){
        pair<int, int> dim1 = m1.getDimention();
        pair<int, int> dim2 = m2.getDimention();

        Matrix result(dim1.first, dim1.second);
        if(dim1.first == dim2.first && dim1.second == dim2.second){
            for(int i=0;i<dim1.first;i++){
                for(int j=0;j<dim1.second;j++){
                    result.setIndex((m1.getIndex(i, j) / m2.getIndex(i, j)), i, j);
                }
            }
        }

        return result;
    }

    Matrix &Product(Matrix &m1, Matrix &m2){

    }

    Matrix &Normalize(Matrix &m){

    }

    Matrix &Transpose(Matrix &m){

    }

    Matrix &Inverse(Matrix &m){

    }
};

int main()
{
    Matrix m1(8, 6);
    m1.print();
    m1.InitializeWithRandom(2);
    m1.print();
    return 0;
}