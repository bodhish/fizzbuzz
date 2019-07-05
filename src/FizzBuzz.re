let str = React.string;

type action =
  | Fizz
  | Buzz
  | FizzBuzz
  | Number;

let fizzbuzz = i =>
  switch (i mod 3, i mod 5) {
  | (0, 0) => FizzBuzz
  | (0, _) => Fizz
  | (_, 0) => Buzz
  | (_, _) => Number
  };

let handleClick = (setScore, action) =>
  setScore(score => action == fizzbuzz(score) ? score + 1 : 1);

let button = (text, action, setScore) =>
  <div
    className="bg-green-500 text-white font-bold py-2 px-4 shadow-lg rounded mt-2 py-2 px-4 text-lg text-center "
    onClick={_ => handleClick(setScore, action)}>
    {text |> str}
  </div>;

let buttonText = (action, number) =>
  switch (action) {
  | Number => number |> string_of_int
  | Fizz => "Fizz"
  | Buzz => "Buzz"
  | FizzBuzz => "FizzBuzz"
  };

[@react.component]
let make = () => {
  let (score, setScore) = React.useState(() => 1);
  <div className="container mx-auto px-2">
    <div className="max-w-md mx-auto">
      <div className="font-bold text-6xl text-center pt-10">
        {"FizzBuzz" |> str}
      </div>
      <div className="font-semibold text-center text-6xl text-green-500">
        {score |> string_of_int |> str}
      </div>
      {
        [|Number, Fizz, Buzz, FizzBuzz|]
        |> Array.map(action =>
             button(buttonText(action, score), action, setScore)
           )
        |> ReasonReact.array
      }
    </div>
  </div>;
};
