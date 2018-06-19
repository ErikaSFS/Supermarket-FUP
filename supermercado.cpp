#include <fstream>
#include <string.h>
#include <cstdio>
#include <stdlib.h>
#include <iomanip>
#include <iostream>

using namespace std;

class produto {

	int produto_id;wew
	char produto_nome[50];
	float produto_preco;
	int produto_quantidade, desconto_produto;

    public:

	void inserir_produto()
	{
		cout<<endl<<"Coloque o id do produto: ";
		cin>>produto_id;
		cout<<endl<<"Coloque o nome do produto: ";
		cin.ignore();
		cin.getline(produto_nome,50);
		cout<<endl<<"Coloque o preço do produto: ";
		cin>>produto_preco;
		cout<<endl<<"Coloque a quantidade do produto no estoque: ";
		cin>>produto_quantidade;
		cout<<endl<<"Coloque o desconto do produto (%): ";
		cin>>desconto_produto;
	}
    void mostrar_produto()
	{
		cout<<endl<<"Produto_ID #: "<<produto_id;
		cout<<endl<<"Produto Nome: "<<produto_nome;
		cout<<endl<<"Produto Preço: "<<produto_preco;
		cout<<endl<<"Produto Quantidade : "<<produto_quantidade;
	}
int getProduto()
	{
		return produto_id;
	}

	float getPreco()
	{
		return produto_preco;
	}

	char* getNome()
	{
		return produto_nome;
	}

	float getQuantidade()
	{
		return produto_quantidade;
	}
	float getDesconto()
	{
		return desconto_produto;
	}
};


fstream sp; //desnvolver o que é
produto produt;

void salvar_produto()
{
	sp.open("prod.txt",ios::out|ios::app);
	produt.inserir_produto();
	sp.write((char*)&produt,sizeof(produto));
	sp.close();
	cout << endl << endl << "O Produto foi salvo com sucesso...";
	getchar(); // olhar o que é
}
 void visualizar_estoque()
{
	system("clear"); //limpar a tela
	cout<<endl<<"\t\t@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@";
	cout<<endl<<"\t\tESTOQUE.";
	cout<<endl<<"\t\t@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@\n";
	sp.open("prod.txt",ios::in);
	while(sp.read((char*)&produt,sizeof(produto)))
	{
		produt.mostrar_produto();
		cout<<endl<<"@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@\n"<<endl;
		getchar();
	}
	sp.close();
}
void exibir_produtos(int num)
{
	bool encontrar=false;
	sp.open("prod.txt",ios::in);
	while(sp.read((char*)&produt,sizeof(produto)))
	{
		if(produt.getProduto()==num)
		{
			system("clear");
			produt.mostrar_produto();
			encontrar=true;
		}
	}

	sp.close();
	if(encontrar == true)
    cout<<"\n\nSem produto inserido";
	getchar();
}
void alterar_produto()
{
	int num;
	bool encontrar=false;
	system("clear");
	cout << endl << endl <<"\tColoque o produto: ";
	cin>>num;

	sp.open("prod.txt",ios::in|ios::out);
	while(sp.read((char*)&produt,sizeof(produto)) && encontrar==false)
	{
		if(produt.getProduto()==num)
		{
			produt.mostrar_produto();
			cout <<"\nColoque a alteração do Produto "<<endl;
			produt.inserir_produto();
			int pos=-1*sizeof(produt);
			sp.seekp(pos,ios::cur);
			sp.write((char*)&produt,sizeof(produto));
			cout << endl << endl << "\t Produto alterado com sucesso...";
			encontrar=true;
		}
	}
	sp.close();
	if(encontrar==false)
		cout << endl << endl << "Produto não encontrado...";
	getchar();
}
void remover_produto()
{
	int num;
	system("clear");
	cout << endl << endl << "Coloque o produto: ";
	cin >> num;
	sp.open("prod.txt",ios::in|ios::out);
	fstream sp2;
	sp2.open("Temp.dat",ios::out);
	sp.seekg(0,ios::beg);
	while(sp.read((char*)&produt,sizeof(produto)))
	{
		if(produt.getProduto()!=num)
		{
			sp2.write((char*)&produt,sizeof(produto));
		}
	}
	sp2.close();
	sp.close();
	remove("prod.txt");
	rename("Temp.dat","prod.txt");
	cout << endl << endl <<"\tProduto delatado...";
	getchar();
}
void menu_produto()
{
	system("clear");
	sp.open("database.dat",ios::in);

	cout << endl << endl <<"\t\t MENU PRODUTO\n\n";
	cout <<"@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@\n";
	cout <<"\t\tID\t\tNOME\t\tPREÇO\tQUANTIDADE EM ESTOQUE\n";
	cout <<"@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@\n";
	while(sp.read((char*)&produt,sizeof(produto)))
	{
		cout<<produt.getProduto()<<"\t\t"<<produt.getNome()<<"\t\t"<<produt.getPreco()<<endl;
	}
	sp.close();
}


void carrinho_compra()
{
	int compra_prod[50],quan[50],c=0;
	float amt,damt,total=0;
	char cr='Y';
	menu_produto();
	cout <<"\n@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@";
	cout <<"\n Adicionar no carrinho";
	cout <<"\n@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@\n";
	do{
		cout<<"\n\n Add no carrinho: ";
		cin >> compra_prod[c];
		cout << "\n Quantidade: ";
		cin >> quan[c];
		c++;
		cout<<"\nVocê quer adicionar outro produto ? (s/n)";
		cin >> cr;
		} while(cr=='s' ||cr=='S');
	cout <<"\n\nObrigada!...";
	getchar();
	system("clear");
	cout <<"\n\n********************************NOTA FISCAL************************\n";
	cout <<"\nID No.\t Nome do Produto \tPreço \tQuantidade em Estoque\n";
	for(int x=0;x<=c;x++)
	{
		sp.open("prod.txt",ios::in);
		sp.read((char*)&produt,sizeof(produto));
		while(!sp.eof())
		{
			if(produt.getProduto()==compra_prod[x])
			{
				amt=produt.getPreco()*quan[x];
				//damt=amt-(amt*produt.getDiscount()/100);
				cout <<"\n" << compra_prod[x]<<"\t"<<produt.getNome()<<"\t"<<quan[x]<<"\t\t"<<produt.getPreco()<<"\t"<<amt<<"\t\t";
				total+=damt;
			}
			sp.read((char*)&produt,sizeof(produto));
		}
		sp.close();
	}
	cout <<"\n\n\t\t\t\t\tTOTAL = "<<total;
	getchar();
}

void menu()
{
	system("clear");
	int digite;
	cout<<"\t#GERENTE DA LOJA#";
	cout<<"\n\tDIGITE 1 PARA INSERIR PRODUTO NO ESTOQUE DA LOJA";
	cout<<"\n\tDIGITE 2 PARA VISUALIZAR NO ESTOQUE DA LOJA";
	cout<<"\n\tDIGITE 3 PARA CONSULTAR O ESTOQUE DA LOJA";
	cout<<"\n\tDIGITE 4 PARA EDITAR PRODUTO DO ESTOQUE";
	cout<<"\n\tDIGITE 5 PARA REMOVER PRODUTO DO ESTOQUE";
	cout<<"\n\tDIGITE 6 VOLTAR AO MENU PRINCIPAL";
	cout<<"\n\t@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@";

	cout <<"\n\n\tDigite a opção: ";
	cin >> digite;
	switch(digite)
	{
		case 1: system("clear");
				salvar_produto();
				break;

		case 2: visualizar_estoque();
				break;

		case 3:
				int num;
				system("clear");
				cout<<"\n\n\tPlease Enter The Product Number: ";
				cin>>num;
				exibir_produtos(num);
				break;

		case 4: alterar_produto();
		        break;

		case 5: remover_produto();
		        break;

		case 6: system("clear");
				break;

		default: menu();
	}
}


int main(int argc, char *argv[])
{
	system("clear");
  	cout<<"\t\t\t\t*\t*";
  	cout<<"\t\t\t\t**\t**";
   	cout<<"\t\t\t\t***\t***";
   	cout<<"\t\t\t\t****\t****";
   	cout<<"\t\t\t\t*****\t*****";
    cout<<"\t\t\t\t******\t******";
   	cout<<"\t\t\t\t*******\t*******";
   	cout<<"\t\t\t\t*******\t*******";
   	cout<<"\t\t\t\t******\t******";
   	cout<<"\t\t\t\t*****\t*****";
   	cout<<"\t\t\t\t****\t****";
   	cout<<"\t\t\t\t***\t***";
   	cout<<"\t\t\t\t**\t**";
   	cout<<"\t\t\t\t*\t*";
	int opcao;

	for(;;)
	{

		cout<<"\n\t@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@";
		cout<<"\n\t1. CLIENTE";
		cout<<"\n\t2. GERENTE";
		cout<<"\n\t3. FIM";
		cout<<"\n\t@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@";

		cout<<"\n\tOpção: ";
		cin>>opcao;

		switch(opcao)
		{
			case 1: system("clear");
					carrinho_compra();
					getchar();
					break;

			case 2: menu();
					break;

			case 3:
					cout<<"\n\t@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@";
					cout<<"\n\tObrigada!";
					cout<<"\n\t@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@\n";
					exit(0);

			default :cout<<"Inválido...\n";
		}

	}
}

