import boto3


dynamodb = boto3.resource('dynamodb')


def lambda_handler(event, context):


    str_Name = event['Name']
    str_Age = event['Age']
    str_Gender = event['Gender']
    str_A = event['A']
    str_B = event['B']
    str_C = event['C']
    str_D = event['D']
    str_E = event['E']
    str_F = event['F']
   
   
    table = dynamodb.Table('User')
    response = table.put_item(
      Item={
            'Name': str_Name,
            'Age': str_Age,
            'Gender' : str_Gender,
            'A' : str_A,
            'B' : str_B,
            'C' : str_C,
            'D' : str_D,
            'E' : str_E,
            'F' : str_F
        }
    )
   
   
    return {
        'statusCode': 200,
        'body': "success"
    }