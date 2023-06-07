package com.example.android_resapi.ui

import android.content.Intent
import android.os.Bundle
import android.view.View
import android.widget.Toast
import androidx.appcompat.app.AppCompatActivity
import com.amazonaws.auth.BasicAWSCredentials
import com.amazonaws.mobile.client.AWSMobileClient
import com.amazonaws.mobile.client.Callback
import com.amazonaws.mobile.client.UserStateDetails
import com.amazonaws.services.s3.AmazonS3Client
import com.amazonaws.services.s3.model.GetObjectRequest
import com.amazonaws.services.s3.model.ObjectMetadata
import com.example.iotprojectreal.AuthActivity
import com.example.iotprojectreal.databinding.ActivityMainBinding
import com.example.iotprojectreal.ui.ListActivity
import com.example.iotprojectreal.ui.NewMemberActivity
import com.example.iotprojectreal.ui.ProductActivity
import com.google.zxing.integration.android.IntentIntegrator
import java.io.BufferedReader
import java.io.ByteArrayInputStream
import java.io.InputStreamReader


class MainActivity : AppCompatActivity() {
    lateinit var binding : ActivityMainBinding
    override fun onCreate(savedInstanceState: Bundle?) {
        super.onCreate(savedInstanceState)
        binding = ActivityMainBinding.inflate(layoutInflater)
        setContentView(binding.root)


        binding.QRButton.setOnClickListener {
            val intent = Intent(this@MainActivity, ListActivity::class.java)
            startActivity(intent)
        }

        binding.logout.setOnClickListener {
            AWSMobileClient.getInstance().initialize(
                applicationContext,
                object : Callback<UserStateDetails?> {
                    override fun onResult(userStateDetails: UserStateDetails?) {
                        // 로그아웃 후 로그인 창으로 이동
                        AWSMobileClient.getInstance().signOut()
                        val i = Intent(this@MainActivity, AuthActivity::class.java)
                        startActivity(i)
                        finish()
                    }

                    override fun onError(e: Exception) {}
                })
        }

        binding.button3.setOnClickListener {
            val intent = Intent(this@MainActivity, NewMemberActivity::class.java)
            startActivity(intent)
        }

        binding.button4.setOnClickListener {
            val intent = Intent(this@MainActivity, ProductActivity::class.java)
            startActivity(intent)
        }


        /*binding.tempButton.setOnClickListener {
            val intent2= Intent(this, TempActivity::class.java)
            intent2.putExtra("thingShadowURL", "https://c3lfnr6yb7.execute-api.us-east-1.amazonaws.com/prod/devices/MKRWiFi10102")
            startActivity(intent2)
        }

        binding.questionButton.setOnClickListener{
            val intent3= Intent(this, QuestionActivity::class.java)
            intent3.putExtra("ultrasonicShadow", "https://qif85maiqj.execute-api.us-east-1.amazonaws.com/items")
            startActivity(intent3)
        }*/


        /*binding.logout.setOnClickListener{
            startActivity(Intent(this, LoginActivity::class.java))
            finish()
        }*/
    }
    fun startQR(view : View){
        IntentIntegrator(this).setCameraId(0).initiateScan()
    }

    override fun onActivityResult(requestCode: Int, resultCode: Int, data: Intent?) {
        val result  = IntentIntegrator.parseActivityResult(requestCode, resultCode, data)
        if(result != null){
            if(result.contents != null){
                Thread {
                    var temp = result.contents
                    temp+='R'
                    sendS3(temp)
                }.start()
                Thread {
                    val s3Object = getS3Object()
                    runOnUiThread {
                        Toast.makeText(this, s3Object, Toast.LENGTH_LONG).show()
                    }
                }.start()
            }else{
                Toast.makeText(this, "값이 존재하지 않습니다", Toast.LENGTH_LONG).show()
            }
        }else{
            super.onActivityResult(requestCode, resultCode, data)
        }
    }

    fun sendS3(content : String){
        val credentials = BasicAWSCredentials("AKIA5EZPEWGEHH4E5PH3", "u6u1hvMNXkW+t1LQPBPPM6RsSbiFEdn8hhp681gg")
        val s3client = AmazonS3Client(credentials)
        val bucketName = "iotsend"
        val objectKey = "app/text"
        val contentBytes = content.toByteArray(Charsets.UTF_8)
        val metadata = ObjectMetadata()
        metadata.contentType = "text/plain"
        val inputStream = ByteArrayInputStream(contentBytes)
        s3client.putObject(bucketName, objectKey, inputStream, metadata)
    }

    fun getS3Object(): String? {
        val credentials = BasicAWSCredentials("AKIA5EZPEWGEHH4E5PH3", "u6u1hvMNXkW+t1LQPBPPM6RsSbiFEdn8hhp681gg")
        val s3client = AmazonS3Client(credentials)
        val s3Object = s3client.getObject(GetObjectRequest("iotsend", "app/text"))
        val inputStream = s3Object.objectContent
        val reader = BufferedReader(InputStreamReader(inputStream))
        val stringBuilder = StringBuilder()
        var line: String?

        while (reader.readLine().also { line = it } != null) {
            stringBuilder.append(line)
        }

        return stringBuilder.toString()
    }
}