#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <iostream>
#include "mysql.h"
#include <string>
#include <conio.h>

using namespace std;

#pragma comment(lib, "libmysql.lib")

const char* host = "localhost";
const char* user = "root";
const char* pw = "mysql";
const char* db = "project";

int main(void) {

	MYSQL* connection = NULL;
	MYSQL conn;
	MYSQL_RES* sql_result;
	MYSQL_ROW sql_row;

	if (mysql_init(&conn) == NULL)
		printf("mysql_init() error!");

	connection = mysql_real_connect(&conn, host, user, pw, db, 3306, (const char*)NULL, 0);
	if (connection == NULL)
	{
		printf("%d ERROR : %s\n", mysql_errno(&conn), mysql_error(&conn));
		return 1;
	}

	else
	{
		printf("Connection Succeed\n\n");

		if (mysql_select_db(&conn, db))
		{
			printf("%d ERROR : %s\n", mysql_errno(&conn), mysql_error(&conn));
			return 1;
		}

		// CRUD 파일 읽기
		FILE* fp;
		fp = fopen("20191637.txt", "r");
		if (fp == NULL) {
			printf("There is no CRUD file.\n");
			return 1;
		}

		// create, insert
		char line[512];
		string str = "";
		int i = 0;
		// create
		for (i = 0; i < 210; i++) {
			fgets(line, sizeof(line), fp);
			str += line;
			if (strcmp(line, ");\n") == 0) {
				const char* query = str.c_str();
				if (mysql_query(connection, query)) {
					fprintf(stderr, "%s\n", mysql_error(connection));
				}
				str = "";
			}
		}
		// insert
		for (; i < 652; i++) {
			fgets(line, sizeof(line), fp);
			str += line;
			if (str.size() == 1)
				continue;
			const char* query = str.c_str();
			if (mysql_query(connection, query)) {
				fprintf(stderr, "%s\n", mysql_error(connection));
			}
			str = "";
		}


		// 쿼리를 수행하는 반복문
		int state = 0;
		do {
			printf("------- SELECT QUERY TYPES -------\n\n");
			printf("\t1. TYPE 1\n");
			printf("\t2. TYPE 2\n");
			printf("\t3. TYPE 3\n");
			printf("\t4. TYPE 4\n");
			printf("\t5. TYPE 5\n");
			printf("\t6. TYPE 6\n");
			printf("\t7. TYPE 7\n");
			printf("\t0. QUIT\n\n");
			printf("----------------------------------\n");
			printf("** Select Query Type: ");
			int select;
			scanf("%d", &select);
			if (select == 0)
				break;
			printf("\n\n");

			// TYPE 1
			if (select == 1) {
				printf("---- TYPE 1 ----\n\n");
				printf("** Assume the package shipped by USPS with tracking number X is reported to have been destroyed in an accident. Find the contact information for the customer.**\n\n");
				printf(" %-20s %-20s\n", "customer", "phone_number");
				printf("+----------------------------------+\n");

				const char* query = "select name, phone_number from delivery natural join customer where tracking_number='X' and company_name='USPS';";
				state = mysql_query(connection, query);
				if (state == 0)
				{
					sql_result = mysql_store_result(connection);
					if ((sql_row = mysql_fetch_row(sql_result)) != NULL)
					{
						printf(" %-20s %-20s\n\n\n", sql_row[0], sql_row[1]);

						printf("------- Subtypes in TYPE 1 -------\n\n");
						printf("\t1. TYPE 1-1\n\n");
						printf("----------------------------------\n");
						printf("** Select SubQuery Type: ");
						int sub;
						scanf("%d", &sub);
						printf("\n\n");

						if (sub == 1) {
							// TYPE 1-1
							printf("---- TYPE 1-1 ----\n\n");
							printf("** Then find the contents of that shipment and create a new shipment of replacement items.**\n\n");

							printf(" %-20s %-20s %-20s %-20s %-14s %-24s %-20s %-20s\n", "tracking number", "shipping_company", "order_date", "customer", "sending_date", "promised_delivery_date", "delivery_address", "issue");
							printf("+----------------------------------------------------------------------------------------------------------------------------------------------------------+\n");

							string tmp = "select * from delivery natural join customer where tracking_number='X' and company_name='USPS';";

							const char* query2 = tmp.c_str();
							state = mysql_query(connection, query2);

							if (state == 0) {
								sql_result = mysql_store_result(connection);
								if ((sql_row = mysql_fetch_row(sql_result)) != NULL) {
									printf(" %-20s %-20s %-20s %-20s %-14s %-24s %-20s %-20s\n\n", sql_row[1], sql_row[2], sql_row[3], sql_row[12], sql_row[5], sql_row[6], sql_row[8], sql_row[10]);

									// Create a new shipment.
									string tmp2 = "insert into delivery (tracking_number, company_name, order_date, order_ID, customer_ID, sending_date, promised_delivery_date, delivery_address, completed) values ('";
									tmp2 += sql_row[1];
									tmp2 += "1', '";
									tmp2 += sql_row[2];
									tmp2 += "', '";
									tmp2 += sql_row[3];
									tmp2 += "', ";
									tmp2 += sql_row[4];
									tmp2 += ", ";
									tmp2 += sql_row[0];
									tmp2 += ", '";
									tmp2 += sql_row[5];
									tmp2 += "', '";
									tmp2 += sql_row[6];
									tmp2 += "', '";
									tmp2 += sql_row[8];
									tmp2 += "', 0);";

									const char* query_tmp = tmp2.c_str();
									if (mysql_query(connection, query_tmp)) {
										fprintf(stderr, "%s\n", mysql_error(connection));
									}

									printf("Success to create a new shipment!\n\n");
								}
							}
						}
						else if (sub == 0)
							break;
					}
					printf("\n\n");
					mysql_free_result(sql_result);
				}
			}
			// TYPE 2
			else if (select == 2) {
				printf("---- TYPE 2 ----\n\n");
				printf("** Find the customer who has bought the most (by price) in the past year.**\n\n");
				printf(" %-20s %-20s %-20s %s\n", "customer", "phone_number", "online_id", "total amount");
				printf("+----------------------------------------------------------------------------+\n");
				const char* query = "with past_year_purchase as (select * from purchase where order_date >= '2021-01-01'), customer_sum_price(customer_ID, sum_price) as(select customer_ID, sum(total_price) as sum_price from past_year_purchase group by customer_ID) select customer_ID, name, phone_number, online_id, sum_price from customer_sum_price natural join customer where sum_price = (select max(sum_price) from customer_sum_price);";
				state = mysql_query(connection, query);
				if (state == 0)
				{
					sql_result = mysql_store_result(connection);
					if ((sql_row = mysql_fetch_row(sql_result)) != NULL)
					{
						printf(" %-20s %-20s %-20s %10s\n\n\n", sql_row[1], sql_row[2], sql_row[3], sql_row[4]);

						printf("------- Subtypes in TYPE 2 -------\n\n");
						printf("\t1. TYPE 2-1\n\n");
						printf("----------------------------------\n");
						printf("** Select SubQuery Type: ");
						int sub;
						scanf("%d", &sub);
						printf("\n\n");

						if (sub == 1) {
							// TYPE 2-1
							printf("---- TYPE 2-1 ----\n\n");
							printf("** Then find the product that the customer bought the most.**\n\n");

							printf(" %-20s %-20s %-20s %s      %s\n", "product", "manufacturer", "type", "price", "number of buying products");
							printf("+---------------------------------------------------------------------------------------------------+\n");

							string tmp = "with max_price_customer as (select * from sales_data where customer_ID = ";
							tmp += sql_row[0];
							tmp += "),product_amount as(select product_ID, manufacturer_name, sum(total_amount) as product_total_amount from max_price_customer group by product_ID, manufacturer_name)select product_name, manufacturer_name, type, price, product_total_amount from product natural join product_amount where product_total_amount = (select max(product_total_amount) from product_amount);";
							const char* query2 = tmp.c_str();
							state = mysql_query(connection, query2);

							if (state == 0) {
								sql_result = mysql_store_result(connection);
								if ((sql_row = mysql_fetch_row(sql_result)) != NULL) {
									printf(" %-20s %-20s %-20s %5s      %25s\n", sql_row[0], sql_row[1], sql_row[2], sql_row[3], sql_row[4]);
								}
							}
						}
						else if (sub == 0)
							break;
					}
					printf("\n\n");
					mysql_free_result(sql_result);
				}
			}
			// TYPE 3
			else if (select == 3) {
				printf("---- TYPE 3 ----\n\n");
				printf("** Find all products sold in the past year.**\n\n");
				printf(" %-20s %-20s %-20s %s\n", "product", "manufacturer", "type", "price");
				printf("+---------------------------------------------------------------------+\n");
				const char* query = "with product_sold as (select product_ID, manufacturer_name from sales_data where order_date >= '2021-01-01'), product_sold_group as(select * from product_sold group by product_ID, manufacturer_name) select product_name, manufacturer_name, type, price from product_sold_group natural join product;";
				state = mysql_query(connection, query);
				if (state == 0)
				{
					int count = 0;	// TYPE 3 쿼리 결과 튜플의 개수 
					sql_result = mysql_store_result(connection);
					while ((sql_row = mysql_fetch_row(sql_result)) != NULL)
					{
						printf(" %-20s %-20s %-20s %5s\n", sql_row[0], sql_row[1], sql_row[2], sql_row[3]);
						count++;
					}
					printf("\n\n");
					printf("------- Subtypes in TYPE 3 -------\n\n");
					printf("\t1. TYPE 3-1\n");
					printf("\t2. TYPE 3-2\n\n");
					printf("----------------------------------\n");
					printf("** Select SubQuery Type: ");
					int sub;
					scanf("%d", &sub);
					printf("\n\n");

					if (sub == 1) {
						// TYPE 3-1
						printf("---- TYPE 3-1 ----\n\n");
						printf("** Then find the top k products by dollar-amount sold.**\n");
						printf(" Which K? : ");
						int k;
						scanf("%d", &k);

						int rank = 1;
						printf("\n %-5s %-20s %-20s %-20s %-5s      %-17s\n", "rank", "product", "manufacturer", "type", "price", "dollar-amount sold");
						printf("+---------------------------------------------------------------------------------------------------+\n");

						string tmp = "with product_sold as (select product_ID, manufacturer_name, total_sales from sales_data where order_date >= '2021-01-01'), product_sold_group as(select product_ID, manufacturer_name, sum(total_sales) as sum_total_sales from product_sold group by product_ID, manufacturer_name order by sum_total_sales desc) select product_name, manufacturer_name, type, price, sum_total_sales from product_sold_group natural join product;";
						const char* query2 = tmp.c_str();
						state = mysql_query(connection, query2);

						if (state == 0) {
							sql_result = mysql_store_result(connection);
							while ((sql_row = mysql_fetch_row(sql_result)) != NULL && rank <= k)
							{
								printf(" %-5d %-20s %-20s %-20s %5s      %17s\n", rank++, sql_row[0], sql_row[1], sql_row[2], sql_row[3], sql_row[4]);
							}
						}
					}
					else if (sub == 2) {
						// TYPE 3-2
						printf("---- TYPE 3-2 ----\n\n");
						printf("** And then find the top 10%% products by dollar-amount sold.**\n");

						printf("\n %-5s %-20s %-20s %-20s %-5s      %-17s\n", "rank", "product", "manufacturer", "type", "price", "dollar-amount sold");
						printf("+---------------------------------------------------------------------------------------------------+\n");

						count = count / 10;
						int rank = 1;
						string tmp = "with product_sold as (select product_ID, manufacturer_name, total_sales from sales_data where order_date >= '2021-01-01'), product_sold_group as(select product_ID, manufacturer_name, sum(total_sales) as sum_total_sales from product_sold group by product_ID, manufacturer_name order by sum_total_sales desc) select product_name, manufacturer_name, type, price, sum_total_sales from product_sold_group natural join product;";
						const char* query2 = tmp.c_str();
						state = mysql_query(connection, query2);

						if (state == 0) {
							sql_result = mysql_store_result(connection);
							while ((sql_row = mysql_fetch_row(sql_result)) != NULL && rank <= count)
							{
								printf(" %-5d %-20s %-20s %-20s %5s      %17s\n", rank++, sql_row[0], sql_row[1], sql_row[2], sql_row[3], sql_row[4]);
							}
						}
					}
					else if (sub == 0)
						break;
					printf("\n\n");
					mysql_free_result(sql_result);
				}
			}
			// TYPE 4
			else if (select == 4) {
				printf("---- TYPE 4 ----\n\n");
				printf("** Find all products by unit sales in the past year.\n\n");
				printf(" %-20s %-20s %-20s %s\n", "product", "manufacturer", "type", "price");
				printf("+---------------------------------------------------------------------+\n");
				const char* query = "with product_sold as (select product_ID, manufacturer_name from sales_data where order_date >= '2021-01-01'), product_sold_group as(select * from product_sold group by product_ID, manufacturer_name) select product_name, manufacturer_name, type, price from product_sold_group natural join product;";
				state = mysql_query(connection, query);
				if (state == 0) {
					int count = 0;	// TYPE 4 쿼리 결과 튜플의 개수 
					sql_result = mysql_store_result(connection);
					while ((sql_row = mysql_fetch_row(sql_result)) != NULL)
					{
						printf(" %-20s %-20s %-20s %5s\n", sql_row[0], sql_row[1], sql_row[2], sql_row[3]);
						count++;
					}
					printf("\n\n");
					printf("------- Subtypes in TYPE 4 -------\n\n");
					printf("\t1. TYPE 4-1\n");
					printf("\t2. TYPE 4-2\n\n");
					printf("----------------------------------\n");
					printf("** Select SubQuery Type: ");
					int sub;
					scanf("%d", &sub);
					printf("\n\n");

					if (sub == 1) {
						// TYPE 4-1
						printf("---- TYPE 4-1 ----\n\n");
						printf("** Then find the top k products by unit sales.**\n");
						printf(" Which K? : ");
						int k;
						scanf("%d", &k);

						int rank = 1;
						printf("\n %-5s %-20s %-20s %-20s %-5s      %-20s\n", "rank", "product", "manufacturer", "type", "price", "number of unit sales");
						printf("+----------------------------------------------------------------------------------------------------+\n");

						string tmp = "with product_sold as (select product_ID, manufacturer_name, total_amount from sales_data where order_date >= '2021-01-01'), product_sold_group as(select product_ID, manufacturer_name, sum(total_amount) as sum_total_number from product_sold group by product_ID, manufacturer_name order by sum_total_number desc) select product_name, manufacturer_name, type, price, sum_total_number from product_sold_group natural join product;";
						const char* query2 = tmp.c_str();
						state = mysql_query(connection, query2);

						if (state == 0) {
							sql_result = mysql_store_result(connection);
							while ((sql_row = mysql_fetch_row(sql_result)) != NULL && rank <= k)
							{
								printf(" %-5d %-20s %-20s %-20s %5s      %20s\n", rank++, sql_row[0], sql_row[1], sql_row[2], sql_row[3], sql_row[4]);
							}
						}
					}
					else if (sub == 2) {
						// TYPE 4-2
						printf("---- TYPE 4-2 ----\n\n");
						printf("** And then find the top 10%% products by unit sales.**\n");

						printf("\n %-5s %-20s %-20s %-20s %-5s      %-20s\n", "rank", "product", "manufacturer", "type", "price", "number of unit sales");
						printf("+----------------------------------------------------------------------------------------------------+\n");

						count = count / 10;
						int rank = 1;
						string tmp = "with product_sold as(select product_ID, manufacturer_name, total_amount from sales_data where order_date >= '2021-01-01'), product_sold_group as(select product_ID, manufacturer_name, sum(total_amount) as sum_total_number from product_sold group by product_ID, manufacturer_name order by sum_total_number desc) select product_name, manufacturer_name, type, price, sum_total_number from product_sold_group natural join product;";
						const char* query2 = tmp.c_str();
						state = mysql_query(connection, query2);

						if (state == 0) {
							sql_result = mysql_store_result(connection);
							while ((sql_row = mysql_fetch_row(sql_result)) != NULL && rank <= count)
							{
								printf(" %-5d %-20s %-20s %-20s %5s      %20s\n", rank++, sql_row[0], sql_row[1], sql_row[2], sql_row[3], sql_row[4]);
							}
						}
					}
					else if (sub == 0)
						break;
					printf("\n\n");
					mysql_free_result(sql_result);
				}
			}
			// TYPE 5
			else if (select == 5) {
				printf("---- TYPE 5 ----\n\n");
				printf("** Find those products that are out-of-stock at every store in California.**\n\n");
				printf(" %-20s %-20s %-20s %s\n", "product", "manufacturer", "type", "price");
				printf("+---------------------------------------------------------------------+\n");
				const char* query = "select product_name, manufacturer_name, type, price from offline_inventory natural join product where region = 'California' and stock = 0;";
				state = mysql_query(connection, query);
				if (state == 0)
				{
					sql_result = mysql_store_result(connection);
					while ((sql_row = mysql_fetch_row(sql_result)) != NULL)
					{
						printf(" %-20s %-20s %-20s %5s\n", sql_row[0], sql_row[1], sql_row[2], sql_row[3]);
					}
					printf("\n\n");
					mysql_free_result(sql_result);
				}
			}
			// TYPE 6
			else if (select == 6) {
				printf("---- TYPE 6 ----\n\n");
				printf("** Find those packages that were not delivered within the promised time.**\n\n");
				printf(" %-20s %-17s %-20s %-20s %-14s %-20s %-20s\n", "shipping_company", "tracking_number", "order_date", "buyer", "delivery_date", "delivery_address", "postman");
				printf("+--------------------------------------------------------------------------------------------------------------------------------+\n");
				const char* query = "select company_name, tracking_number, order_date, name, delivery_date, delivery_address, shipper_name from delivery natural join customer where completed=2;";
				state = mysql_query(connection, query);
				if (state == 0)
				{
					sql_result = mysql_store_result(connection);
					while ((sql_row = mysql_fetch_row(sql_result)) != NULL)
					{
						printf(" %-20s %-17s %-20s %-20s %-14s %-20s %-20s\n", sql_row[0], sql_row[1], sql_row[2], sql_row[3], sql_row[4], sql_row[5], sql_row[6]);
					}
					printf("\n\n");
					mysql_free_result(sql_result);
				}
			}
			// TYPE 7
			else if (select == 7) {
				printf("---- TYPE 7 ----\n\n");
				printf("** Generate the bill for each customer for the past month.**\n\n");
				const char* query = "select * from bill where due_date >= '2022-06-30';";
				state = mysql_query(connection, query);
				if (state == 0)
				{
					sql_result = mysql_store_result(connection);
					while ((sql_row = mysql_fetch_row(sql_result)) != NULL)
					{
						string query2 = "insert into bill values (";
						int bill_number = (atoi(sql_row[0]) + 1);
						query2 += to_string(bill_number);
						query2 += ", '";
						query2 += sql_row[1];
						query2 += "', '";
						query2 += sql_row[2];
						query2 += "', '";
						query2 += sql_row[3];
						query2 += "', ";
						query2 += sql_row[4];
						query2 += ", ";
						query2 += sql_row[5];
						query2 += ", '2022-06-30', '";
						query2 += sql_row[7];
						query2 += "', ";
						query2 += sql_row[8];
						query2 += ", ";
						query2 += sql_row[9];
						query2 += ");";

						const char* query_tmp = query2.c_str();
						if (mysql_query(connection, query_tmp)) {
							fprintf(stderr, "%s\n", mysql_error(connection));
						}
					}
					printf("Success to generate the bill for each customer for the past month!\n\n");
					mysql_free_result(sql_result);
				}
			}
			else
				continue;
		} while (1);


		// delete and drop
		for (; i < 691; i++) {
			fgets(line, sizeof(line), fp);
			str += line;
			if (str.size() == 1)
				continue;
			const char* query = str.c_str();
			if (mysql_query(connection, query)) {
				fprintf(stderr, "%s\n", mysql_error(connection));
			}
			str = "";
		}


		fclose(fp);
		mysql_close(connection);
	}

	return 0;
}