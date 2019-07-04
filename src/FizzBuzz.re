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
    className="bg-blue-500 hover:bg-blue-700 text-white font-bold py-2 px-4 border border-blue-700 rounded mt-2"
    onClick={_ => handleClick(setScore, action)}>
    {text |> str}
  </div>;

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
      {button(score |> string_of_int, Number, setScore)}
      {button("Fizz", Fizz, setScore)}
      {button("Buzz", Buzz, setScore)}
      {button("FizzBuzz", FizzBuzz, setScore)}
    </div>
  </div>;
};
