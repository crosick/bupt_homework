"""haha

Revision ID: 3bcd2b30bd88
Revises: 1ffb6adc7af1
Create Date: 2015-12-05 22:28:10.586021

"""

# revision identifiers, used by Alembic.
revision = '3bcd2b30bd88'
down_revision = '1ffb6adc7af1'

from alembic import op
import sqlalchemy as sa


def upgrade():
    ### commands auto generated by Alembic - please adjust! ###
    op.create_unique_constraint(None, 'users', ['username'])
    ### end Alembic commands ###


def downgrade():
    ### commands auto generated by Alembic - please adjust! ###
    op.drop_constraint(None, 'users')
    ### end Alembic commands ###
