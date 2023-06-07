package com.example.iotprojectreal.ui

import android.os.Bundle
import androidx.appcompat.app.AppCompatActivity
import com.amazonaws.mobile.client.AWSMobileClient
import com.amazonaws.mobile.client.Callback
import com.amazonaws.mobile.client.UserStateDetails
import com.example.iotprojectreal.R
import com.example.iotprojectreal.databinding.ActivityNewmemberBinding
import okhttp3.MediaType.Companion.toMediaTypeOrNull
import okhttp3.RequestBody
import okhttp3.ResponseBody
import org.json.JSONObject
import retrofit2.Call
import retrofit2.Response
import retrofit2.Retrofit
import retrofit2.converter.gson.GsonConverterFactory
import retrofit2.http.Body
import retrofit2.http.POST


class NewMemberActivity : AppCompatActivity() {

    lateinit var binding : ActivityNewmemberBinding
    override fun onCreate(savedInstanceState : Bundle?){
        super.onCreate(savedInstanceState)
        binding = ActivityNewmemberBinding.inflate(layoutInflater)
        setContentView(binding.root)

        var age = 0
        var gen = ""
        var Name = ""
        AWSMobileClient.getInstance().initialize(
            applicationContext,
            object : Callback<UserStateDetails?> {
                override fun onResult(userStateDetails: UserStateDetails?) {
                    val sub = AWSMobileClient.getInstance().userAttributes.get("sub").toString()
                    Name = sub
                }
                override fun onError(e: Exception) {}
            })


        binding.radioGroup1.setOnCheckedChangeListener{ _, checkdId ->
            when(checkdId){
                R.id.age1 -> {
                    age = 1
                }
                R.id.age2 -> {
                    age = 2
                }
                R.id.age3 -> {
                    age = 3
                }
                R.id.age4 -> {
                    age = 4
                }
            }
        }
        binding.radioGroup2.setOnCheckedChangeListener { _, checkdId ->
            when(checkdId){
                R.id.man -> {
                    gen = "male"
                }
                R.id.woman -> {
                    gen = "female"
                }
            }
        }

        binding.completeButton.setOnClickListener {
            val A = binding.A.text
            val B = binding.B.text
            val C = binding.C.text
            val D = binding.D.text
            val E = binding.E.text
            val F = binding.F.text
            val retrofit = Retrofit.Builder()
                .baseUrl("https://sex7ys3fn8.execute-api.ap-northeast-2.amazonaws.com/test/")
                .addConverterFactory(GsonConverterFactory.create())
                .build()
            val apiInterface = retrofit.create(MyApi::class.java)
            val jsonObject = JSONObject()
            jsonObject.put("Name", Name)
            jsonObject.put("Age", age)
            jsonObject.put("Gender", gen)
            jsonObject.put("A", A)
            jsonObject.put("B", B)
            jsonObject.put("C", C)
            jsonObject.put("D", D)
            jsonObject.put("E", E)
            jsonObject.put("F", F)

            val requestBody = RequestBody.create("application/json".toMediaTypeOrNull(), jsonObject.toString())

            apiInterface.postData(requestBody).enqueue(object : Callback<ResponseBody?>,
                retrofit2.Callback<ResponseBody> {
                override fun onResult(result: ResponseBody?) {
                    TODO("Not yet implemented")
                }

                override fun onError(e: java.lang.Exception?) {
                    TODO("Not yet implemented")
                }

                override fun onResponse(
                    call: Call<ResponseBody>,
                    response: Response<ResponseBody>
                ) {
                    System.out.println(Name + age + gen)
                    System.out.println("성공")
                    onBackPressed()
                }

                override fun onFailure(call: Call<ResponseBody>, t: Throwable) {
                    TODO("Not yet implemented")
                }
            })

        }

        /*binding.completeButton.setOnClickListener{
            val userEmail = binding.username2.text.toString()
            val password = binding.password2.text.toString()
            val selected1 = binding.radioGroup1.checkedRadioButtonId
            val selected2 = binding.radioGroup2.checkedRadioButtonId
            if(userEmail == "" || password == "" || selected1 == -1 || selected2 == -1){
                Toast.makeText(this, "필수 값을 입력하세요.", Toast.LENGTH_SHORT).show()
            }else {
                //signUp(userEmail, password, gen, age, "")
            }
        }*/
    }

    /*private fun doSignUp(userEmail: String, password: String, age : Int, gen : Int){
        Firebase.auth.createUserWithEmailAndPassword(userEmail, password).addOnCompleteListener { task ->
            if(task.isSuccessful){
                val uid = Firebase.auth.currentUser?.uid
                val db : FirebaseFirestore = Firebase.firestore
                val userRef = db.collection("user")
                val userMap = hashMapOf(
                    "uid" to uid,
                    "age" to age,
                    "gender" to gen
                )
                userRef.document(uid.toString()).set(userMap)
            }else{
                Toast.makeText(this, "계정 생성에 실패하였습니다.", Toast.LENGTH_SHORT).show()
            }
        }
        onBackPressed()
    }*/

}
interface MyApi {
    @POST("greeting")
    fun postData(@Body requestBody: RequestBody): Call<ResponseBody>
}
