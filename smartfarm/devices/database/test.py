from sqlalchemy import create_engine
from sqlalchemy import MetaData, Table, Column, Integer, Numeric, String, ForeignKey,Boolean, DateTime
from datetime import datetime
#url = 'sqlite:///Users/chatchaivichai/project/MyFarm/smartfarm/cookies.db'
url = 'sqlite:///:memory:'
engine = create_engine(url,echo=True) 
connection = engine.connect()
metadata = MetaData()

cookies = Table('cookies', metadata,
    Column('cookie_id', Integer(), primary_key=True),
    Column('cookie_name', String(50), index=True),
    Column('cookie_recipe_url', String(255)),
    Column('cookie_sku', String(55)),
    Column('quantity', Integer()),
    Column('unit_cost', Numeric(12, 2))
)
users = Table('users', metadata,
    Column('user_id', Integer(), primary_key=True),
    Column('customer_number', Integer(), autoincrement=True),
    Column('username', String(15), nullable=False, unique=True),
    Column('email_address', String(255), nullable=False),
    Column('phone', String(20), nullable=False),
    Column('password', String(25), nullable=False),
    Column('created_on', DateTime(), default=datetime.now),
    Column('updated_on', DateTime(), default=datetime.now, onupdate=datetime.now)
)
orders = Table('orders', metadata,
    Column('order_id', Integer(), primary_key=True),
    Column('user_id', ForeignKey('users.user_id'))
)
line_items = Table('line_items', metadata,
    Column('line_items_id', Integer(), primary_key=True),
    Column('order_id', ForeignKey('orders.order_id')),
    Column('cookie_id', ForeignKey('cookies.cookie_id')),
    Column('quantity', Integer()),
    Column('extended_cost', Numeric(12, 2))
)
metadata.create_all(engine)

ins = cookies.insert().values(
    cookie_name="chocolate chip",
    cookie_recipe_url="http://some.aweso.me/cookie/recipe.html",
    cookie_sku="CC01",
    quantity="12",
    unit_cost="0.50"
    )

#print(str(ins))
#print(str(ins.compile().params))

result = connection.execute(ins)
print(str(result))

inventory_list = [
    {
    'cookie_name': 'peanut butter',
    'cookie_recipe_url': 'http://some.aweso.me/cookie/peanut.html',
    'cookie_sku': 'PB01',
    'quantity': '24',
    'unit_cost': '0.25'
    }, {
    'cookie_name': 'oatmeal raisin',
    'cookie_recipe_url': 'http://some.okay.me/cookie/raisin.html',
    'cookie_sku': 'EWW01',
    'quantity': '100',
    'unit_cost': '1.00'
    } 
]
multiple_ins = cookies.insert(inventory_list)

resuls = connection.execute(multiple_ins)

from sqlalchemy import select
s = select([cookies])
rp = connection.execute(s)
result = rp.fetchall()
print(str(result))

for first_row in result:
    print(str(first_row[0]))
    print(first_row[1])
    print(first_row.keys())
#first_row.c.cookie_name