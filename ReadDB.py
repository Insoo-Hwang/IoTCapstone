import json
import boto3
    
def lambda_handler(event, context):
    dynamodb = boto3.resource('dynamodb')

    product = dynamodb.Table('Product')
    
    response = product.get_item(Key={'Location': '1'})
    product_item1 = response['Item']
    A = (product_item1.get('Name') if product_item1 else None)
    B = str(product_item1.get('Price') if product_item1 else None)
    
    response = product.get_item(Key={'Location': '2'})
    product_item2 = response['Item']
    C = (product_item2.get('Name') if product_item1 else None)
    D = str(product_item2.get('Price') if product_item1 else None)
    
    response = product.get_item(Key={'Location': '3'})
    product_item3 = response['Item']
    E = (product_item3.get('Name') if product_item1 else None)
    F = str(product_item3.get('Price') if product_item1 else None)
    
    response = product.get_item(Key={'Location': '4'})
    product_item4 = response['Item']
    G = (product_item4.get('Name') if product_item1 else None)
    H = str(product_item4.get('Price') if product_item1 else None)
    
    iot_client = boto3.client('iot-data')
    payload1 =  {'message2' : A,
               'message3':  B
              }
    payload2 =  {'message2' : C,
               'message3':  D
              }
    payload3 =  {'message2' : E,
               'message3':  F
              }
    payload4 =  {'message2' : G,
               'message3':  H
              }


    response = iot_client.publish(
        topic='intopic1',
        qos=1,
        payload=json.dumps(payload1)
    )
    response = iot_client.publish(
        topic='intopic2',
        qos=1,
        payload=json.dumps(payload2)
    )
    response = iot_client.publish(
        topic='intopic3',
        qos=1,
        payload=json.dumps(payload3)
    )
    response = iot_client.publish(
        topic='intopic4',
        qos=1,
        payload=json.dumps(payload4)
    )
        
    return {
        'statusCode': 200,
        'body': json.dumps('Hello from Lambda!')
    }