let str = React.string;

[@react.component]
let make = () => {
  let fizzbuzz = i => {
    switch(i mod 3 , i mod 5){
    | (0,0) => "FizzBuzz"
    | (0,_) => "Fizz"
    | (_,0) => "Buzz"
    | (_,_) => i |> string_of_int
    };
  };

  for (i in 1 to 100) { Js.log(fizzbuzz(i))};
  <div> <h1> {"FizzBuzz" |> str} </h1> </div>
};
