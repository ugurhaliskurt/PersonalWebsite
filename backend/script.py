import psycopg2

def connect():
    conn = psycopg2.connect(
        dbname="mydatabase",
        user="user",
        password="password",
        host="postgres",
        port="5432"
    )
    print("Connected to database!")
    conn.close()

if __name__ == "__main__":
    connect()
