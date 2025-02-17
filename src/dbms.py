import mysql.connector
import mysql.connector.cursor
# script unser Development
connection = mysql.connector.connect(
    host="localhost", user="root", password="new_password")
cursor = connection.cursor()
cursor.execute("Show databases")
for row in cursor.fetchall():
    print(row)
