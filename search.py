import json
import boto3
from boto3.dynamodb.conditions import Key


def lambda_handler(event, context):
    dynamodb = boto3.resource('dynamodb')
   
    table = dynamodb.Table('Product')
   
    str_Location = event['Location']
   
   
    response = table.query(
        KeyConditionExpression=Key('Location').eq(str_Location)
    )

    if len(response['Items']) == 0:
        return {
            'statusCode': 200,
            'body':json.dumps({
            "Location": "not found",
            "Name": "not found",
            "Price": "not found"
            })
        }
   
    else:
        r = response['Items'][0]
        r["Price"] = str(r["Price"])

        return {
            'statusCode': 200,
            'body':json.dumps({
            "Location": r["Location"],
            "Name": r["Name"],
            "Price": r["Price"]
            })

        }
